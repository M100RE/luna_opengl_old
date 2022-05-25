cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(renderer)

find_package(glfw3 3.3 REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(renderer main.cpp ${SRC_FILES} libs/glad/src/glad.c)

target_link_libraries(renderer glfw)

target_include_directories(renderer PUBLIC include libs/glad/include libs/glfw/include)