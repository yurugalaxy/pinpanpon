cmake_minimum_required(VERSION 3.20)

# Commented out when using replit
# cmake_minimum_required(VERSION 3.30)

project(pinpanpon)

set(CMAKE_CXX_STANDARD 23)

link_libraries(SDL2)

add_executable(${PROJECT_NAME} 
                src/main.cpp)
