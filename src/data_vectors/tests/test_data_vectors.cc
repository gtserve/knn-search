#include <gtest/gtest.h>
#include <vector>
#include <cmath>

#include "../data_vector.h"

using namespace std;

TEST(TestDataVector, EmptyVector) {
  vector<int> v1;
  DataVector<int> dv(v1);
  EXPECT_EQ(dv.getSize(), 0);
}

TEST(TestDataVector, OneVector) {
  vector<int> v1 = {0};
  DataVector<int> dv(v1);
  EXPECT_EQ(dv.getSize(), 1);
}

TEST(TestDataVector, FiveVector) {
  vector<int> v1 = {1, 2, 3, 4, 5};
  DataVector<int> dv(v1);
  EXPECT_EQ(dv.getSize(), 5);
}

TEST(TestDataVector, TestDistanceFromVector) {
  vector<int> v1 = {4, 1};
  vector<int> v2 = {3, 0};

  DataVector<int> dv1(v1);

  EXPECT_EQ(dv1.getDistance(v2), sqrt(2));
}

TEST(TestDataVector, TestDistanceFromDataVector) {
  vector<int> v1 = {4, 1};
  vector<int> v2 = {3, 0};

  DataVector<int> dv1(v1);
  DataVector<int> dv2(v2);

  EXPECT_EQ(dv1.getDistance(&dv2), sqrt(2));
}

TEST(TestDataVector, Filters) {
  vector<int> v = {1, 2, 3, 4, 5};
  set<float> f = {9, 10};
  DataVector<int> dv(v, f);
  dv.print();
  EXPECT_EQ(dv.getSize(), 5);
}
