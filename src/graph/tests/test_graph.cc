#include <gtest/gtest.h>
#include <graph.h>

TEST(TestGraph, Test1) {
    vector<vector <int>> data;
    for (int i = 0; i < 10; i++)
        vector<int> v = {i, i, i, i, i};

    graph<int> G(data);
    G.generate_random_graph(3);
    G.print_graph();
}