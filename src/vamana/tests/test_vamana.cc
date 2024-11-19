#include <gtest/gtest.h>
#include <graph.h>
#include <vamana.h>
#include <ctime>

TEST(TestGreedySearch, Test1) {
    vector<vector<int>> data;
    for (int i = 0; i < 10; i++) {
        vector<int> v = {i, i, i, i, i};
        data.push_back(v);
    }

    graph<int> G(data);
    G.generate_random_graph(3);
    G.print();

    pair<set<int>, set<int>> temp_pair = greedy_graph_search(&G, 0, 2, data[2], 2, 10, false);
    for (const int i: temp_pair.first) cout << i << endl;
    ASSERT_EQ(temp_pair.first.size(), 2);
}

TEST(TestVamana, Test1) {

    vector<vector <int>> data;
    for (int i = 0; i < 10; i++)
        vector<int> v = {i, i, i, i, i};

    graph<int> G(data);
    const int medoid_id = medoid(data);
    vamana(&G, data, medoid_id, 2.0, 5, 4);
    G.print();
}

TEST(TestVamana_Random, Test2) {
    srand(time(NULL));

    vector<vector <int>> data;
    for (int i = 0; i < 10; i++)
        vector<int> v = {(rand() % 100), (rand() % 100), (rand() % 100), (rand() % 100), (rand() % 100)};

    graph<int> G(data);
    const int medoid_id = medoid(data);

    vamana(&G, data, medoid_id, 1.2, 10, 4);
    G.print();
}
