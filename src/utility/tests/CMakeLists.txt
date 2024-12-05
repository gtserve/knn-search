cmake_minimum_required(VERSION 3.28.3)
project(k23a_project)

add_executable(
        test_util
        test_util.cc
)

target_link_libraries(
        test_util
        GTest::gtest_main
        util_library
        input_library
)

add_test(NAME TestUtil COMMAND test_util)
