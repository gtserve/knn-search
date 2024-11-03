#include <gtest/gtest.h>
#include <vector>
#include <cmath>

#include "../data_vector.h"

using namespace std;

TEST(DataPointTest, EmptyVector) {
  vector<int> v1;
  DataVector<int> dv(v1);
  EXPECT_EQ(dv.getSize(), 0);
}

TEST(DataPointTest, OneVector) {
  vector<int> v1 = {0};
  DataVector<int> dv(v1);
  EXPECT_EQ(dv.getSize(), 1);
}

TEST(DataPointTest, FiveVector) {
  vector<int> v1 = {1, 2, 3, 4, 5};
  DataVector<int> dv(v1);
  EXPECT_EQ(dv.getSize(), 5);
}

TEST(TestEclidean, Test1) {
  vector<int> v1 = {4, 1};
  vector<int> v2 = {3, 0};

  DataVector<int> dv1(v1);
  DataVector<int> dv2(v2);

  EXPECT_EQ(dv1.getDistance(&dv2), sqrt(2));
}
