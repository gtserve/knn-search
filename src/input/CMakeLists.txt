cmake_minimum_required(VERSION 3.28)
project(k23a_project)

set(CMAKE_CXX_STANDARD 20)

add_library(input_library input.cpp)

target_include_directories(input_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)
