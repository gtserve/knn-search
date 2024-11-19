cmake_minimum_required(VERSION 3.28.3)
project(k23a_project)

add_executable(
        test_data_vector
        test_data_vectors.cc
)

target_link_libraries(
        test_data_vector
        GTest::gtest_main
        data_vector_library
)

add_test(NAME TestDataVector COMMAND test_data_vector)
