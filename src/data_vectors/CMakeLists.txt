cmake_minimum_required(VERSION 3.28)
project(k23a_project)

set(CMAKE_CXX_STANDARD 20)

add_library(data_vector_library data_vector.cpp)

target_include_directories(data_vector_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)
