cmake_minimum_required(VERSION 3.25)

project(ZeroOs VERSION 0.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} wiringPi)

add_subdirectory(libs/ST7789)
target_link_libraries(${PROJECT_NAME} ST7789)

add_subdirectory(libs/zGfx)
target_link_libraries(${PROJECT_NAME} zGfx)
