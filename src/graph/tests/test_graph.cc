#include <gtest/gtest.h>
#include <graph.h>

TEST(TestGraph, TestEmpty) {
    graph<int> G({});

    EXPECT_EQ(G.get_vertices(), 0);
}

TEST(TestGraph, TestSimpleGraph) {
    vector<vector<int>> vecs;
    for (int i = 0; i < 10; i++)
        vecs.push_back(vector<int>({i, i, i, i, i}));

    graph<int> G(vecs);
    EXPECT_EQ(G.get_vertices(), 10);
}

TEST(TestGraph, TestRandomGeneratedGraph) {
    vector<vector<int>> vecs;
    for (int i = 0; i < 10; i++)
        vecs.push_back(vector<int>({i, i, i, i, i}));

    graph<int> G(vecs);
    G.generate_random_graph(3);
    G.print();
}

TEST(TestGraph, TestNeighbours) {
    vector<vector<int>> vecs;
    for (int i = 0; i < 10; i++)
        vecs.push_back(vector<int>({i, i, i, i, i}));

    graph<int> G(vecs);
    G.generate_random_graph(3);

    unordered_set<int> neighbours = G.getNodeNeighbours(0);
    EXPECT_EQ(neighbours.size(), 3);
}

TEST(TestGraph, TestClearNeighbours) {
    vector<vector<int>> vecs;
    for (int i = 0; i < 10; i++)
        vecs.push_back(vector<int>({i, i, i, i, i}));

    graph<int> G(vecs);
    G.generate_random_graph(3);
    G.clearNeighbours(0);

    unordered_set<int> neighbours = G.getNodeNeighbours(0);
    EXPECT_EQ(neighbours.size(), 0);
}
