cmake_minimum_required(VERSION 3.2)
project(ping)

set(CMAKE_CXX_STANDARD 23)

# find_package(SDL2_REQUIRED)

link_libraries(SDL2)

add_executable(${PROJECT_NAME} 
                src/main.cpp
                src/game.cpp
                src/game.hpp)
