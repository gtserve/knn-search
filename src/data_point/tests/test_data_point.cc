#include <gtest/gtest.h>
#include <vector>

#include "../data_point.h"

using namespace std;

TEST(DataPointTest, EmptyVector) {
  vector<int> v1;
  DataPoint<int> dp(v1);
  EXPECT_EQ(dp.getSize(), 0);
}

TEST(DataPointTest, OneVector) {
  vector<int> v1 = {0};
  DataPoint<int> dp(v1);
  EXPECT_EQ(dp.getSize(), 1);
}

TEST(DataPointTest, FiveVector) {
  vector<int> v1 = {1, 2, 3, 4, 5};
  DataPoint<int> dp(v1);
  EXPECT_EQ(dp.getSize(), 5);
}
