cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(homework_VERSION_MAJOR 3)
set(homework_VERSION_MINOR 0)
set(homework_VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})

project(allocator VERSION
        ${homework_VERSION_MAJOR}.${homework_VERSION_MINOR}.${homework_VERSION_BUILD})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(HEADER_FILES
        homework_tools.h
        logging_allocator.h
        allocator.h)

add_executable(allocator main.cpp
        ${HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR}/version.h)

add_library(allocator_tools homework_tools.cpp ${HEADER_FILES})

add_executable(test_version test_version.cpp ${HEADER_FILES})

set_target_properties(allocator allocator_tools test_version PROPERTIES
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(allocator allocator_tools)

target_link_libraries(test_version ${Boost_LIBRARIES} allocator_tools)

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_CONTACT "sysdos286@yahoo.com")
set(CPACK_PACKAGE_VERSION_MAJOR ${homework_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${homework_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${homework_VERSION_BUILD})

include(CPack)

enable_testing()

add_test(test_version test_version)

message(STATUS "Homework version ${homework_VERSION_MAJOR}.${homework_VERSION_MINOR}")

