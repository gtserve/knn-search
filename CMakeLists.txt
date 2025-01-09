cmake_minimum_required(VERSION 3.28)
project(k23a_project)

set(CMAKE_CXX_STANDARD 17)

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
)

add_executable(index_vamana index_vamana.cpp)

target_link_libraries(
        index_vamana
        input_library
        util_library
        data_vector_library
        graph_library
        vamana_library
)

add_executable(query_index query_index.cpp)
target_link_libraries(
        query_index
        input_library
        util_library
        data_vector_library
        graph_library
        vamana_library
)

set_target_properties(gtest PROPERTIES SYSTEM TRUE)
set_target_properties(gmock PROPERTIES SYSTEM TRUE)
