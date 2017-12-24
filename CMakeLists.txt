cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(homework_VERSION_MAJOR 2)
set(homework_VERSION_MINOR 1)
set(homework_VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})

project(ip_filter VERSION
        ${homework_VERSION_MAJOR}.${homework_VERSION_MINOR}.${homework_VERSION_BUILD})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(HEADER_FILES ip_filter.h)

add_executable(ip_filter main.cpp
        ${HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR}/version.h)

add_library(ip_filter_tools ip_filter.cpp ${HEADER_FILES})

add_executable(test_version test_version.cpp ${HEADER_FILES})

target_compile_options(ip_filter PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(ip_filter_tools PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(test_version PRIVATE -Wpedantic -Wall -Wextra)

set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(ip_filter ip_filter_tools)

target_link_libraries(test_version ${Boost_LIBRARIES} ip_filter_tools)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_CONTACT "sysdos286@yahoo.com")
set(CPACK_PACKAGE_VERSION_MAJOR ${homework_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${homework_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${homework_VERSION_BUILD})

include(CPack)

enable_testing()

add_test(test_version test_version)

message(STATUS "Homework version ${homework_VERSION_MAJOR}.${homework_VERSION_MINOR}")

