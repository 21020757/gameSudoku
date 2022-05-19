cmake_minimum_required(VERSION 3.21)
project(untitled)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled main.cpp game.cpp game.h grid.h header.h random.cpp solve.h solve.cpp)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(untitled PRIVATE SDL2::SDL2 SDL2::SDL2main)

find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(untitled PRIVATE SDL2::SDL2_image)

find_package(sdl2-ttf CONFIG REQUIRED)
target_link_libraries(untitled PRIVATE SDL2::SDL2_ttf)

find_package(sdl2-mixer CONFIG REQUIRED)
target_link_libraries(untitled PRIVATE SDL2::SDL2_mixer)