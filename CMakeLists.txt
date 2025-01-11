cmake_minimum_required(VERSION 3.28)
project(k23a_project)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(src/input)
add_subdirectory(src/data_vectors)
add_subdirectory(src/utility)
add_subdirectory(src/graph)
add_subdirectory(src/vamana)

add_executable(
        main
        main.cpp
)

target_link_libraries(
        main
        input_library
        util_library
        data_vector_library
        graph_library
        vamana_library
)

add_executable(
        main_2
        main_2.cpp
)

target_link_libraries(
        main_2
        input_library
        util_library
        data_vector_library
        graph_library
        vamana_library
)

add_executable(main_3 main_3.cpp)

target_link_libraries(
        main_3
        input_library
        util_library
        data_vector_library
        graph_library
        vamana_library
        OpenMP::OpenMP_CXX
)

add_executable(index_v index_v.cpp)

target_link_libraries(
        index_v
        input_library
        util_library
        data_vector_library
        graph_library
        vamana_library
        OpenMP::OpenMP_CXX
)

add_executable(query_index_v query_index_v.cpp)
target_link_libraries(
        query_index_v
        input_library
        util_library
        data_vector_library
        graph_library
        vamana_library
        OpenMP::OpenMP_CXX
)

add_executable(index_fv index_fv.cpp)
target_link_libraries(
        index_fv
        input_library
        util_library
        data_vector_library
        graph_library
        vamana_library
        OpenMP::OpenMP_CXX
)

add_executable(query_index_fv query_index_fv.cpp)
target_link_libraries(
        query_index_fv
        input_library
        util_library
        data_vector_library
        graph_library
        vamana_library
        OpenMP::OpenMP_CXX
)

add_executable(index_sv index_sv.cpp)
target_link_libraries(
        index_sv
        input_library
        util_library
        data_vector_library
        graph_library
        vamana_library
        OpenMP::OpenMP_CXX
)

add_executable(query_index_sv query_index_sv.cpp)
target_link_libraries(
        query_index_sv
        input_library
        util_library
        data_vector_library
        graph_library
        vamana_library
        OpenMP::OpenMP_CXX
)

set_target_properties(gtest PROPERTIES SYSTEM TRUE)
set_target_properties(gmock PROPERTIES SYSTEM TRUE)
