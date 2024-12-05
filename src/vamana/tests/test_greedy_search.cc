#include <gtest/gtest.h>
#include <graph.h>
#include <vamana.h>
#include <ctime>

TEST(TestGreedySearch, LinearGraph) {
    /*
     * Input:
     *      Graph: A(0) -> B(1) -> C(2) -> D(3)
     *      Distances: A->B=1, B->C=1, C->D=1
     *      Start: A
     *      Query: D
     *      Result size: k=2
     *      Search list size: L=3
     */

    vector<float> vA = {0.0};
    vector<float> vB = {1.0};
    vector<float> vC = {2.0};
    vector<float> vD = {3.0};
    vector<vector<float>> vecs = {vA, vB, vC, vD};

    graph<float> G(vecs);
    G.addEdgeDirected(0, 1);
    G.addEdgeDirected(1, 2);
    G.addEdgeDirected(2, 3);

    pair<unordered_set<int>, unordered_set<int>> result = greedy_graph_search(&G, 0, 3, vD, 2, 3, false);
    unordered_set<int> L = result.first;
    unordered_set<int> V = result.second;

    /*
    * Expected Output:
    *      L: D, C              (Query is in graph)
    *      V: {A, B, C, D}
    */

    EXPECT_TRUE(L.find(3) != L.end());
    EXPECT_TRUE(L.find(2) != L.end());

    EXPECT_TRUE(V.find(1) != L.end());
    EXPECT_TRUE(V.find(2) != L.end());
    EXPECT_TRUE(V.find(3) != L.end());
    EXPECT_TRUE(V.find(4) != L.end());
}

TEST(TestGreedySearch, TwoWayLinearGraph) {
    /*
     * Input:
     *      Graph: A(0) <-> B(1) <-> C(2) <-> D(3)
     *      Distances: A<->B=1, B<->C=1, C<->D=1
     *      Start: A
     *      Query: C
     *      Result size: k=2
     *      Search list size: L=3
     */

    vector<float> vA = {0.0};
    vector<float> vB = {1.0};
    vector<float> vC = {2.0};
    vector<float> vD = {3.0};
    vector<vector<float>> vecs = {vA, vB, vC, vD};

    graph<float> G(vecs);
    G.addEdgeDirected(0, 1);
    G.addEdgeDirected(1, 0);
    G.addEdgeDirected(1, 2);
    G.addEdgeDirected(2, 1);
    G.addEdgeDirected(2, 3);
    G.addEdgeDirected(3, 2);

    pair<unordered_set<int>, unordered_set<int>> result = greedy_graph_search(&G, 0, 2, vC, 2, 3, false);
    unordered_set<int> L = result.first;
    unordered_set<int> V = result.second;

    /*
    * Expected Output:
    *      L: B, C              (B is explored before D)
    *      V: {A, B, C, D}
    */

    EXPECT_TRUE(L.find(1) != L.end());
    EXPECT_TRUE(L.find(2) != L.end());

    EXPECT_TRUE(V.find(1) != L.end());
    EXPECT_TRUE(V.find(2) != L.end());
    EXPECT_TRUE(V.find(3) != L.end());
    EXPECT_TRUE(V.find(4) != L.end());
}

TEST(TestGreedySearch, QueryNotInGraph) {
    /*
     * Input:
     *      Graph: A(0) -> B(1) -> C(2) -> D(3)
     *      Distances: A->B=1, B->C=1, C->D=1
     *      Start: A
     *      Query: Q(1.5)
     *      Result size: k=2
     *      Search list size: L=3
     */

    vector<float> vA = {0.0};
    vector<float> vB = {1.0};
    vector<float> vC = {2.0};
    vector<float> vD = {3.0};
    vector<float> vQ = {1.5};
    vector<vector<float>> vecs = {vA, vB, vC, vD};

    graph<float> G(vecs);
    G.addEdgeDirected(0, 1);
    G.addEdgeDirected(1, 2);
    G.addEdgeDirected(2, 3);

    pair<unordered_set<int>, unordered_set<int>> result = greedy_graph_search(&G, 0, 0, vQ, 2, 3, false);
    unordered_set<int> L = result.first;
    unordered_set<int> V = result.second;

    /*
    * Expected Output:
    *      L: B, C
    *      V: {A, B, C, D}
    */

    EXPECT_TRUE(L.find(1) != L.end());
    EXPECT_TRUE(L.find(2) != L.end());

    EXPECT_TRUE(V.find(1) != L.end());
    EXPECT_TRUE(V.find(2) != L.end());
    EXPECT_TRUE(V.find(3) != L.end());
    EXPECT_TRUE(V.find(4) != L.end());
}

TEST(TestGreedySearch, SparseGraph) {
    /*
     * Input:
     *      Graph:
     *          A(0) <-> B(1),
     *          A(0) <-> C(2),
     *          B(1) <-> D(3)
     *
     *      Distances: A<->B=2, A<->C=5, B<->D=3
     *      Start: A
     *      Query: D
     *      Result size: k=2
     *      Search list size: L=3
     */

    vector<float> vA = {0.0};
    vector<float> vB = {2.0};
    vector<float> vC = {5.0};
    vector<float> vD = {5.0};
    vector<vector<float>> vecs = {vA, vB, vC, vD};

    graph<float> G(vecs);
    G.addEdgeDirected(0, 1);
    G.addEdgeDirected(1, 2);
    G.addEdgeDirected(2, 3);

    pair<unordered_set<int>, unordered_set<int>> result = greedy_graph_search(&G, 0, 3, vD, 2, 3, false);
    unordered_set<int> L = result.first;
    unordered_set<int> V = result.second;

    /*
    * Expected Output:
    *      L: D, C
    *      V: {A, B, C, D}
    */

    EXPECT_TRUE(L.find(2) != L.end());
    EXPECT_TRUE(L.find(3) != L.end());

    EXPECT_TRUE(V.find(1) != L.end());
    EXPECT_TRUE(V.find(2) != L.end());
    EXPECT_TRUE(V.find(3) != L.end());
    EXPECT_TRUE(V.find(4) != L.end());
}