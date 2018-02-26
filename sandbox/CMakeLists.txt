add_executable(test_list test_list.cpp)

add_executable(log_allocator log_allocator.cpp)

add_executable(min_allocator min_allocator.cpp)

target_compile_options(log_allocator PRIVATE -Wpedantic -Wall -Wextra -I${CMAKE_SOURCE_DIR})
