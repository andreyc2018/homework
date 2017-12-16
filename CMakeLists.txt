cmake_minimum_required(VERSION 3.2)

set (homework_VERSION_MAJOR 2)
set (homework_VERSION_MINOR 0)
set (homework_VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})

project(homework VERSION ${homework_VERSION_MAJOR}.${homework_VERSION_MINOR}.${homework_VERSION_BUILD})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(ip_filter main.cpp)

add_library(ip_filter_tools ip_filter.cpp)

add_executable(test_version test_version.cpp)

set_target_properties(ip_filter ip_filter_tools test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

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
