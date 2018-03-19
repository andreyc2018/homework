cmake_minimum_required(VERSION 3.9)
project(async_example)

set(CMAKE_CXX_STANDARD 14)

add_library(async_example SHARED async.cpp async.h)

add_executable(async_cli main.cpp)

target_link_libraries(async_cli async_example)
