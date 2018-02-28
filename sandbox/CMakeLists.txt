add_executable(map_iterator map_iterator.cpp)

target_compile_options(map_iterator PRIVATE -Wpedantic -Wall -Wextra -I${CMAKE_SOURCE_DIR})

add_executable(value_iterator value_iterator.cpp)

target_compile_options(value_iterator PRIVATE -Wpedantic -Wall -Wextra -I${CMAKE_SOURCE_DIR})
