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

enable_testing()

add_executable(
        test_data_point
        test_data_vectors.cc
)

target_link_libraries(
        test_data_point
        GTest::gtest_main
        data_point_library
)

#target_include_directories(hello_test PRIVATE ${CMAKE_SOURCE_DIR}/parent)

include(GoogleTest)
gtest_discover_tests(test_data_point)
