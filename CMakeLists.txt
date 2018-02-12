cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if ($ENV{TRAVIS_BUILD_NUMBER})
    set(BUILD_NUM $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(BUILD_NUM 99)
endif()

set(homework_VERSION_MAJOR 8)
set(homework_VERSION_MINOR 0)
set(homework_VERSION_BUILD ${BUILD_NUM})

project(homework VERSION
        ${homework_VERSION_MAJOR}.${homework_VERSION_MINOR}.${homework_VERSION_BUILD})

configure_file(version.h.in version.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(hieroglyphs hieroglyphs.cpp
        docs/1545-Hieroglyphs.md docs/hw_assignment.md
        ${HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR}/version.h)
add_executable(spammer spammer.cpp
        docs/1496-Spammer.md docs/hw_assignment.md
        ${HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR}/version.h)
add_executable(history_exam history_exam.cpp
        docs/1196-History_Exam.md docs/hw_assignment.md
        ${HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR}/version.h)
add_executable(isenbaev_s_number isenbaev_s_number.cpp
        docs/1837-Isenbaev_s_Number.md docs/hw_assignment.md
        ${HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR}/version.h)

target_compile_options(hieroglyphs PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(spammer PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(history_exam PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(isenbaev_s_number PRIVATE -Wpedantic -Wall -Wextra)

message(STATUS "Homework version
        ${homework_VERSION_MAJOR}.${homework_VERSION_MINOR}.${homework_VERSION_BUILD}")
