cmake_minimum_required(VERSION 3.17)

project(fast_collection)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_subdirectory(fast_allocator)