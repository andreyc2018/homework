cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if ($ENV{TRAVIS_BUILD_NUMBER})
    set(BUILD_NUM $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(BUILD_NUM 99)
endif()

set(homework_VERSION_MAJOR 11)
set(homework_VERSION_MINOR 0)
set(homework_VERSION_BUILD ${BUILD_NUM})

project(async VERSION
        ${homework_VERSION_MAJOR}.${homework_VERSION_MINOR}.${homework_VERSION_BUILD})

configure_file(version.h.in version.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(HEADER_FILES observers.h logger.h
        interpreter.h command.h
        processor.h parser.h
        parserstate.h)

add_library(bulk_tools
        interpreter.cpp
        processor.cpp
        parser.cpp
        parserstate.cpp
        ${HEADER_FILES})

add_executable(async main.cpp docs/hw_assignment.md
        ${HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR}/version.h)
add_executable(intergrate_gtest_gmock intergrate_gtest_gmock.cpp)
add_executable(test_version test_bulk.cpp ${HEADER_FILES})

target_compile_options(async PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(bulk_tools PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(intergrate_gtest_gmock PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(test_version PRIVATE -Wpedantic -Wall -Wextra)

target_include_directories(intergrate_gtest_gmock PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include)
target_include_directories(intergrate_gtest_gmock PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include)
target_include_directories(test_version PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include)
target_include_directories(test_version PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include)

target_link_libraries(async bulk_tools)
target_link_libraries(intergrate_gtest_gmock gmock_main)
target_link_libraries(test_version bulk_tools gmock_main)

install(TARGETS async RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_CONTACT "sysdos286@yahoo.com")
set(CPACK_PACKAGE_VERSION_MAJOR ${homework_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${homework_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${homework_VERSION_BUILD})

include(CPack)

enable_testing()

add_test(NAME intergrate_gtest_gmock COMMAND intergrate_gtest_gmock)
add_test(NAME test_version COMMAND test_version)

add_subdirectory(example)

if(EXISTS ${CMAKE_SOURCE_DIR}/sandbox/CMakeLists.txt)
    add_subdirectory(sandbox EXCLUDE_FROM_ALL)
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/googletest/CMakeLists.txt)
    # Replace install() to do-nothing macro.
    macro(install)
    endmacro()
    # Include subproject (or any other CMake code) with "disabled" install().
    message(STATUS "Adding Google Test framework.")
    add_subdirectory(googletest)
    # Restore original install() behavior.
    macro(install)
        _install(${ARGN})
    endmacro()
endif()

message(STATUS "Homework version
    ${homework_VERSION_MAJOR}.${homework_VERSION_MINOR}.${homework_VERSION_BUILD}")

find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/README.md
            ${CMAKE_CURRENT_BINARY_DIR}/docs/README.md COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/hw_assignment.md
            ${CMAKE_CURRENT_BINARY_DIR}/docs/hw_assignment.md COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/_config.yml
            ${CMAKE_CURRENT_BINARY_DIR}/docs/_config.yml COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/parser_state_machine.uml
            ${CMAKE_CURRENT_BINARY_DIR}/docs/parser_state_machine.uml COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/parser_state_machine.png
            ${CMAKE_CURRENT_BINARY_DIR}/docs/html/parser_state_machine.png COPYONLY)

    # note the option ALL which allows to build the docs together with the application
    #add_custom_target(doc_doxygen ALL
    add_custom_target(doc_doxygen
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

