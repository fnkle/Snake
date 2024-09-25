cmake_minimum_required(VERSION 3.10)
project(Snake)
find_package(SDL2)



include_directories(${SDL2_INCLUDE_DIR})

add_executable(Snake ./src/main.cpp)

target_include_directories(Snake PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Snake ${SDL2_LIBRARIES})
