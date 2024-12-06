#include <gtest/gtest.h>
#include <graph.h>
#include <utility_functions.h>

#define GRAPH_DIR "."


TEST(TestGraph, TestEmpty) {
    graph<int> G({}, 0);

    EXPECT_EQ(G.getNumNodes(), 0);
}

TEST(TestGraph, TestSimpleGraph) {
    vector<vector<int> > vecs;
    for (int i = 0; i < 10; i++)
        vecs.push_back(vector<int>({i, i, i, i, i}));

    graph<int> G(vecs);
    EXPECT_EQ(G.getNumNodes(), 10);
}

TEST(TestGraph, TestRandomGeneratedGraph) {
    vector<vector<int> > vecs;
    for (int i = 0; i < 10; i++)
        vecs.push_back(vector<int>({i, i, i, i, i}));

    graph<int> G(vecs);
    G.generate_random_graph(3);
    G.print();
}

TEST(TestGraph, TestNeighbours) {
    vector<vector<int> > vecs;
    for (int i = 0; i < 10; i++)
        vecs.push_back(vector<int>({i, i, i, i, i}));

    graph<int> G(vecs);
    G.generate_random_graph(3);


    unordered_set<int> neighbours = G.getNodeNeighbours(0);
    EXPECT_EQ(neighbours.size(), 3);
}

TEST(TestGraph, TestClearNeighbours) {
    vector<vector<int> > vecs;
    for (int i = 0; i < 10; i++)
        vecs.push_back(vector<int>({i, i, i, i, i}));

    graph<int> G(vecs);
    G.generate_random_graph(3);
    G.clearNeighbours(0);


    unordered_set<int> neighbours = G.getNodeNeighbours(0);
    EXPECT_EQ(neighbours.size(), 0);
}

TEST(TestGraph, SaveLoadBinaryFile) {
    vector<vector<float> > data_vectors = {
        {1.1, 1.2, 1.3, 1.4, 1.5},
        {2.1, 2.2, 2.3, 2.4, 2.5},
        {3.1, 3.2, 3.3, 3.4, 3.5},
        {4.1, 4.2, 4.3, 4.4, 4.5},
        {5.1, 5.2, 5.3, 5.4, 5.5}
    };
    vector<vector<float> > filters {{1.0}, {2.0}, {3.0}, {4.0}, {5.0}};

    int R = 5;

    graph<float> Ga(data_vectors, R, filters);
    Ga.generate_random_graph(R);
    // Ga.print(true);
    string file_name = Ga.saveGraphToDir(GRAPH_DIR);

    graph<float> Gb(file_name);
    // Gb.print(true);

    EXPECT_EQ(Ga.getNumNodes(), Gb.getNumNodes());

    for (int i = 0; i < data_vectors.size(); i++)
        EXPECT_EQ(Ga.get_node(i)->getComponents(), Gb.get_node(i)->getComponents());

    for (int i = 0; i < data_vectors.size(); i++)
        for (const auto &n: Gb.getNodeNeighbours(i))
            EXPECT_TRUE(Ga.getNodeNeighbours(i).find(n) != Ga.getNodeNeighbours(i).end());

}
