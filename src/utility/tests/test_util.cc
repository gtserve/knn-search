#include <gtest/gtest.h>
#include <utility_functions.h>

TEST(TestUtil, RandomPermutation) {
    vector<int> v = randomPermutation(10);
    for (int i: v) cout << i << " ";
    cout << endl;
}