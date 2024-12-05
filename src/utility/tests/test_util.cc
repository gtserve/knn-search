#include <gtest/gtest.h>
#include <utility_functions.h>
#include <algorithm>
#include <input.h>
#include <unordered_set>

TEST(TestUtil, RandomPermutation) {
    vector<int> v = randomPermutation(10);
    EXPECT_TRUE(std::find(v.begin(), v.end(), 0) != v.end());
    EXPECT_TRUE(std::find(v.begin(), v.end(), 1) != v.end());
    EXPECT_TRUE(std::find(v.begin(), v.end(), 2) != v.end());
    EXPECT_TRUE(std::find(v.begin(), v.end(), 3) != v.end());
    EXPECT_TRUE(std::find(v.begin(), v.end(), 4) != v.end());
    EXPECT_TRUE(std::find(v.begin(), v.end(), 5) != v.end());
    EXPECT_TRUE(std::find(v.begin(), v.end(), 6) != v.end());
    EXPECT_TRUE(std::find(v.begin(), v.end(), 7) != v.end());
    EXPECT_TRUE(std::find(v.begin(), v.end(), 8) != v.end());
    EXPECT_TRUE(std::find(v.begin(), v.end(), 9) != v.end());
}

TEST(TestUtil, Recall) {
    unordered_set<int> X = {1, 2, 3, 99, 102};
    unordered_set<int> T = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_NEAR(recall(X, T), 0.6, 0.001);
}

TEST(TestUtil, EuclideanDistance) {
    vector<float> v1 = {3.0, -2.0, 5.0};
    vector<float> v2 = {-1.0, 4.0, 2.0};
    EXPECT_NEAR(euclidean_distance(v1, v2), sqrt(61), 0.001);
}
