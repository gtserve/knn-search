cmake_minimum_required(VERSION 3.28)
project(k23a_project)

add_library(
        graph_library
        graph.cpp
        vector_node.cpp
)

target_link_libraries(
        graph_library
        data_vector_library
)

target_include_directories(graph_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)
