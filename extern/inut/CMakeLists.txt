cmake_minimum_required(VERSION 3.1)

include_directories(include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")

add_subdirectory(example)
add_subdirectory(src)
add_subdirectory(lib/array)
