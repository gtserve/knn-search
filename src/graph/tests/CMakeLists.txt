cmake_minimum_required(VERSION 3.28.3)
project(k23a_project)

add_executable(
        test_graph
        test_graph.cc
)

target_link_libraries(
        test_graph
        GTest::gtest_main
        graph_library
)

add_test(NAME TestGraph COMMAND test_graph)
