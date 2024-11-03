cmake_minimum_required(VERSION 3.28)
project(k23a_project)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/input)
add_subdirectory(src/data_vectors)
add_subdirectory(src/utility)
add_subdirectory(src/graph)
add_subdirectory(src/vamana)

add_executable(
        hello
        main.cpp
)
