cmake_minimum_required(VERSION 3.28.3)
project(k23a_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

enable_testing()

add_executable(
        test_input_small
        test_input_small.cc
)

target_link_libraries(
        test_input_small
        GTest::gtest_main
        input_library
)

gtest_discover_tests(test_input_small)

add_executable(
        test_input
        test_input.cc
)

target_link_libraries(
        test_input
        GTest::gtest_main
        input_library
)

gtest_discover_tests(test_input)
