#include <gtest/gtest.h>
#include <vector>

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
  DataVector<int> dv  (v1);
  EXPECT_EQ(dv.getSize(), 5);
}
