cmake_minimum_required(VERSION 3.10)

project(opengl)

add_executable(${PROJECT_NAME} main.c)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(GL QUIET gl)

target_link_libraries(${PROJECT_NAME} PRIVATE
  ${SDL2_LIBRARIES}
  ${GL_LIBRARIES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${SDL2_INCLUDE_DIRS}
)

if(PSP)
    create_pbp_file(
        TARGET ${PROJECT_NAME}
        ICON_PATH NULL
        BACKGROUND_PATH NULL
        PREVIEW_PATH NULL
        TITLE ${PROJECT_NAME}
        VERSION 01.00
    )
endif()
