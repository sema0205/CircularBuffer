cmake_minimum_required(VERSION 3.12)

project(
        lab8
        VERSION 1.0
        DESCRIPTION "C++ Year 2022 Lab8"
        LANGUAGES CXX
)


set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)