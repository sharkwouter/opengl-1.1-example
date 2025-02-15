#include <stdio.h>

#include <SDL.h>

#define NO_SDL_GLEXT
#include <SDL_opengl.h>

SDL_Window * window = NULL;
SDL_GLContext glcontext;

#ifdef __PSP__
# define WIDTH 480
# define HEIGHT 272
#else
# define WIDTH 800
# define HEIGHT 800
#endif

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

  glEnable(GL_DEPTH_TEST);
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

void draw_cube() {
  GLfloat face1[] = {
    -0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    -0.5, -0.5, 0.5,

    0.5, -0.5, 0.5,
    -0.5, -0.5, 0.5,
    0.5, 0.5, 0.5,
  };

  GLfloat face2[] = {
    -0.5, 0.5, 0.5,
    -0.5, 0.5, -0.5,
    -0.5, -0.5, 0.5,

    -0.5, -0.5, -0.5,
    -0.5, 0.5, -0.5,
    -0.5, -0.5, 0.5,
  };

  GLfloat face3[] = {
    -0.5, 0.5, -0.5,
    0.5, 0.5, -0.5,
    -0.5, -0.5, -0.5,

    0.5, -0.5, -0.5,
    -0.5, -0.5, -0.5,
    0.5, 0.5, -0.5,
  };

  GLfloat face4[] = {
    0.5, 0.5, 0.5,
    0.5, 0.5, -0.5,
    0.5, -0.5, 0.5,

    0.5, -0.5, -0.5,
    0.5, 0.5, -0.5,
    0.5, -0.5, 0.5,
  };

  GLfloat face5[] = {
    0.5, -0.5, -0.5,
    -0.5, -0.5, -0.5,
    0.5, -0.5, 0.5,

    -0.5, -0.5, 0.5,
    -0.5, -0.5, -0.5,
    0.5, -0.5, 0.5,
  };

  GLfloat face6[] = {
    0.5, 0.5, -0.5,
    -0.5, 0.5, -0.5,
    0.5, 0.5, 0.5,

    -0.5, 0.5, 0.5,
    -0.5, 0.5, -0.5,
    0.5, 0.5, 0.5,
  };

  glEnableClientState(GL_VERTEX_ARRAY);

  glColor3f(1.0, 0.0, 0.0);
  glVertexPointer(3, GL_FLOAT, 0, face1);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glColor3f(0.0, 0.0, 1.0);
  glVertexPointer(3, GL_FLOAT, 0, face2);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glColor3f(0.0, 1.0, 0.0);
  glVertexPointer(3, GL_FLOAT, 0, face3);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glColor3f(0.0, 1.0, 1.0);
  glVertexPointer(3, GL_FLOAT, 0, face4);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glColor3f(1.0, 0.0, 1.0);
  glVertexPointer(3, GL_FLOAT, 0, face5);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glVertexPointer(3, GL_FLOAT, 0, face6);
  glColor3f(1.0, 1.0, 0.0);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glDisableClientState(GL_VERTEX_ARRAY);

  print_gl_errors();
}

int main(int argc, char *argv[]) {
  init("OpenGL 1.1 Example", WIDTH, HEIGHT);

  SDL_Event event;
  GLboolean running = GL_TRUE;
  while (running) {
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          running = GL_FALSE;
          break;
        case SDL_WINDOWEVENT:
          if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
            int w, h;
            SDL_GetWindowSize(window, &w, &h);
            glViewport(0, 0, (GLsizei) w, (GLsizei) h);
          }
          break;
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_ESCAPE) {
            running = GL_FALSE;
          }
      }
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(1, 1.0, 1.0, 0);

    draw_cube();

    glFlush();
    SDL_GL_SwapWindow(window);
  }
  cleanup();
}