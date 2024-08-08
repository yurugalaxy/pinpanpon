cmake_minimum_required(VERSION 3.30)
project(ping)

set(CMAKE_CXX_STANDARD 23)

link_libraries(SDL2)
link_libraries(SDL2_image)

add_executable(${PROJECT_NAME} 
                src/main.cpp)
