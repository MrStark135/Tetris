cmake_minimum_required(VERSION 4.0.3)
set(CMAKE_CXX_STANDARD 11)

project(Tetris VERSION 1.0)

file(GLOB sources ./src/*.cpp)

find_package(SDL2 REQUIRED)

add_executable(Tetris ./src/main.cpp ${sources})

target_include_directories(Tetris PRIVATE ./include)
target_link_libraries(Tetris SDL2 SDL2main SDL2_image SDL2_ttf)