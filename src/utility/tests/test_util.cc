#include <gtest/gtest.h>
#include <utility_functions.h>
#include <chrono>
#include <input.h>

TEST(TestUtil, RandomPermutation) {
    vector<int> v = randomPermutation(10);
    for (int i: v) cout << i << " ";
    cout << endl;
}

TEST(TestUtil, Recall) {
    auto time_start = std::chrono::system_clock::now();

    set<int> X = {1, 2, 3, 99, 102};
    set<int> T = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto time_end = std::chrono::system_clock::now();
    // chrono::duration<double> elapsed_seconds = time_end - time_start;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(time_end - time_start);
    cout << duration.count() << " ms" << endl;

    EXPECT_NEAR(recall(X, T), 0.6, 0.001);
}

TEST(TestDistance, GroundTruth) {
    vector<vector<float>> base_vectors;
    readVectors<float> ("/home/gtserve/Code/k23a-project/data/siftsmall/siftsmall_base.fvecs", base_vectors);

    vector<vector<float>> query_vectors;
    readVectors<float> ("/home/gtserve/Code/k23a-project/data/siftsmall/siftsmall_query.fvecs", query_vectors);

    vector<vector<int>> gt_vectors;
    readVectors<int> ("/home/gtserve/Code/k23a-project/data/siftsmall/siftsmall_groundtruth.ivecs", gt_vectors);

    int query_id = 0;
    vector<float> query_vector = query_vectors[0];

    vector<pair<long double, int>> distances;
    for (const int i: gt_vectors[0]) {
        long double dist = euclidean_distance(query_vector, base_vectors[i]);
        distances.push_back({dist, i});
        // cout << i << " " << dist << endl;
    }
    sort(distances.begin(), distances.end());

    for (const int i: gt_vectors[0]) {
        cout << i << " ";
    }
    cout << endl;

    for (const pair d: distances) {
        cout << d.second << " ";
    }
    cout << endl;
}