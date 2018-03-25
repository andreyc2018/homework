set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(threads threads.cpp)

install(TARGETS threads RUNTIME DESTINATION bin)
