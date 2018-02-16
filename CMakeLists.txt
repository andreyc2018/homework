cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

set(EXECUTABLE_NAME matrix)
set(LIBRARY_NAME matrix_tool)
set(TEST_NAME matrix_test)

if ($ENV{TRAVIS_BUILD_NUMBER})
    set(BUILD_NUM $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(BUILD_NUM 99)
endif()

set(homework_VERSION_MAJOR 6)
set(homework_VERSION_MINOR 0)
set(homework_VERSION_BUILD ${BUILD_NUM})

project(${EXECUTABLE_NAME} VERSION
    ${homework_VERSION_MAJOR}.${homework_VERSION_MINOR}.${homework_VERSION_BUILD})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(HEADER_FILES matrix.h)

add_executable(${EXECUTABLE_NAME} main.cpp
    ${HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR}/version.h)

add_library(${LIBRARY_NAME} matrix.cpp ${HEADER_FILES})

add_executable(${TEST_NAME} matrix_test.cpp ${HEADER_FILES})

target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(${LIBRARY_NAME} PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(${TEST_NAME} PRIVATE -Wpedantic -Wall -Wextra)

set_target_properties(${TEST_NAME} PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_NAME})

target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES} ${LIBRARY_NAME})

install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_CONTACT "sysdos286@yahoo.com")
set(CPACK_PACKAGE_VERSION_MAJOR ${homework_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${homework_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${homework_VERSION_BUILD})

include(CPack)

enable_testing()

add_test(${TEST_NAME} ${TEST_NAME})

if(EXISTS ${CMAKE_SOURCE_DIR}/sandbox/CMakeLists.txt)
    add_subdirectory(sandbox EXCLUDE_FROM_ALL)
endif()

message(STATUS "Homework version
    ${homework_VERSION_MAJOR}.${homework_VERSION_MINOR}.${homework_VERSION_BUILD}")

