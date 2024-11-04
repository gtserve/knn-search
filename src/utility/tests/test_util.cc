#include <gtest/gtest.h>
#include <utility_functions.h>

TEST(TestUtil, RandomPermutation) {
    vector<int> v = randomPermutation(10);
    for (int i: v) cout << i << " ";
    cout << endl;
}

TEST(TestUtil, Recall) {
    set<int> X = {1, 2, 3, 99, 102};
    set<int> T = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_NEAR(recall(X, T), 0.6, 0.001);
}
