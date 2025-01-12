cmake_minimum_required(VERSION 3.28)
project(k23a_project)

find_package(OpenMP REQUIRED)

add_library(
        util_library
        utility_functions.cpp
)

target_link_libraries(
        util_library
        data_vector_library
        OpenMP::OpenMP_CXX
)

target_include_directories(util_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)
