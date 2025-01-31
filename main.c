#include <stdio.h>

#include <SDL2/SDL.h>
#include <GL/gl.h>

SDL_Window * window = NULL;
SDL_GLContext glcontext;


void cleanup() {
  SDL_GL_DeleteContext(glcontext);
  if (window != NULL) {
    SDL_DestroyWindow(window);
  }
  SDL_Quit();
}

void init(const char * title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER | SDL_INIT_TIMER) != 0) {
    printf("Failed to initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }
  window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (!window) {
    printf("couldn't create window: %s\n", SDL_GetError());
    cleanup();
    exit(2);
  }
  SDL_GLContext * glcontext = SDL_GL_CreateContext(window);
  if (!glcontext) {
    printf("couldn't create GL context: %s\n", SDL_GetError());
    cleanup();
    exit(3);
  }

  // glEnableClientState(GL_VERTEX_ARRAY);
  // glEnableClientState(GL_COLOR_ARRAY);
}

void print_gl_errors(){
  GLenum error;
  while (error = glGetError()) {
    switch (error) {
      case GL_INVALID_OPERATION:
        printf("Error: Operation illegal in current state, command ignored\n");
        break;
      case GL_INVALID_VALUE:
        printf("Error: Numeric argument out of range, command ignored\n");
        break;
      case GL_INVALID_ENUM:
        printf("Error: enum argument out of range, command ignored\n");
        break;
      case GL_STACK_OVERFLOW:
        printf("Error: Command would cause stack overflow, command ignored\n");
        break;
      case GL_STACK_UNDERFLOW:
        printf("Error: Command would cause stack underflow, command ignored\n");
        break;
      case GL_OUT_OF_MEMORY:
        printf("Error: Not enough memory left to execute command, who knows what happens now\n");
        break;
      default:
        printf("Unknown error %i! This error is not in the OpenGL 1.1 spec!\n", error);
        break;
    }
  }
}

void render_something() {
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_TRIANGLES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex2f(0, 0.5);
  
  glColor3f(0.0, 1.0, 0.0);
  glVertex2f(0.5, -0.5);

  glColor3f(0.0, 0.0, 1.0);
  glVertex2f(-0.5, -0.5);
  glEnd();

  print_gl_errors();

  glFlush();

  SDL_GL_SwapWindow(window);
}

int main(int argc, char *argv[]) {
  init("splitshot", 1280, 720);

  SDL_Event event;
  GLboolean running = GL_TRUE;
  while (running) {
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          running = GL_FALSE;
          break;
      }
    }
    render_something();
  }
  cleanup();
}