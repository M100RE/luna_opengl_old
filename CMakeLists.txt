cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(luna)

find_package(glfw3 3.3 REQUIRED)

set(LUNA_INCLUDE_DIRS include libs/glad/include libs/glfw/include)
set(LUNA_LIBRARIES glfw)

file(GLOB_RECURSE SRC_FILES src/*.cpp)



add_library(luna ${SRC_FILES} libs/glad/src/glad.c)

target_link_libraries(luna ${LUNA_LIBRARIES})

target_include_directories(luna PUBLIC ${LUNA_INCLUDE_DIRS})
