cmake_minimum_required(VERSION 3.28.3)
project(k23a_project)

add_executable(
        test_input_small
        test_input_small.cc
)

target_link_libraries(
        test_input_small
        GTest::gtest_main
        input_library
)

add_executable(
        test_input
        test_input.cc
)

target_link_libraries(
        test_input
        GTest::gtest_main
        input_library
)

add_test(NAME TestInputSmall COMMAND test_input_small)
add_test(NAME TestInput COMMAND test_input)
