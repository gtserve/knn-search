cmake_minimum_required(VERSION 3.28.3)
project(k23a_project)

add_executable(
        test_vamana
        test_greedy_search.cc
)

target_link_libraries(
        test_vamana
        GTest::gtest_main
        graph_library
        vamana_library
)

add_test(NAME TestVamana COMMAND test_vamana)
