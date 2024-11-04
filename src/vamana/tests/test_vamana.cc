#include <gtest/gtest.h>
#include <graph.h>
#include <vamana.h>

TEST(TestGreedySearch, Test1) {
    vector<DataVector<int> *> data;
    for (int i = 0; i < 10; i++) {
        vector<int> v = {i, i, i, i, i};
        data.push_back(new DataVector<int>(v));
    }

    graph<int> G(data);
    G.generate_random_graph(3);
    G.print_graph();

    pair<set<int>, set<int>> temp_pair = greedy_graph_search(&G, 0, 2, 2, 10);
    for (const int i: temp_pair.first) cout << i << endl;
    ASSERT_EQ(temp_pair.first.size(), 2);

    for (int i = 0; i < 10; i++) {
        delete(data[i]);
    }
}

TEST(TestSets, Test1) {
    set<pair<int, double>, compare_by_second_value> s1;
    set<pair<int, double>, compare_by_second_value> s2;
    set<pair<int, double>, compare_by_second_value> diff;
    s1.insert({0, 4.47});
    s1.insert({5, 6.72});
    s1.insert({7, 9.92});
    s1.insert({1, 1.12});
    s2.insert({5, 6.72});
    s2.insert({7, 9.92});
    set_difference(
        s1.begin(), s1.end(),
        s2.begin(), s2.end(),
        inserter(diff, diff.begin())
    );
    for (const auto pair: diff) {
        cout << pair.first << " " << pair.second << endl;
    }
}

TEST(TestVamana, Test1) {
    vector<DataVector<int> *> data;
    for (int i = 0; i < 10; i++) {
        vector<int> v = {i, i, i, i, i};
        data.push_back(new DataVector<int>(v));
    }

    graph<int> G(data);

    vamana(&G, &data, 2.0, 10, 4);
    G.print_graph();

    for (int i = 0; i < 10; i++) {
        delete(data[i]);
    }
}