cmake_minimum_required(VERSION 3.10)
project(Snake)
find_package(SDL2)



include_directories(${SDL2_INCLUDE_DIR})
include_directories("include/")

file(GLOB_RECURSE ${PROJECT_NAME}_SRC "src/*.cpp")
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRC})

target_link_libraries(Snake ${SDL2_LIBRARIES})
