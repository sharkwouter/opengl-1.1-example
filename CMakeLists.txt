cmake_minimum_required(VERSION 3.10)

project(splitshot)

add_executable(${PROJECT_NAME} main.c)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(GL QUIET gl)

target_link_libraries(${PROJECT_NAME} PRIVATE
  ${SDL2_LIBRARIES}
  ${GL_LIBRARIES}
)
