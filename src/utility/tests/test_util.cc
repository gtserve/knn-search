#include <gtest/gtest.h>
#include <utility_functions.h>
#include <chrono>

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
    cout << duration << " microseconds" << endl;

    EXPECT_NEAR(recall(X, T), 0.6, 0.001);
}
