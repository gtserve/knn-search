#include <gtest/gtest.h>
#include <graph.h>

TEST(TestGraph, Test1) {
    vector<DataVector<int> *> data;
    for (int i = 0; i < 10; i++) {
        vector<int> v = {i, i, i, i, i};
        data.push_back(new DataVector<int>(v));
    }

    graph<int> G(data);
    G.generate_random_graph(3);
    G.print_graph();

    for (int i = 0; i < 10; i++) {
        delete(data[i]);
    }
}