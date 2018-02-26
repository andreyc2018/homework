add_executable(map_iterator map_iterator.cpp)

target_compile_options(map_iterator PRIVATE -Wpedantic -Wall -Wextra -I${CMAKE_SOURCE_DIR})

