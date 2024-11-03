cmake_minimum_required(VERSION 3.28)
project(k23a_project)

set(CMAKE_CXX_STANDARD 20)

add_library(vamana_library vamana.tpp)

target_link_libraries(
        vamana_library
        graph_library
)

target_include_directories(vamana_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#add_subdirectory(tests)
