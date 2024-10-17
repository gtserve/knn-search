cmake_minimum_required(VERSION 3.28)
project(k23a_project)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(tests)

add_executable(hello src/main.cpp)
