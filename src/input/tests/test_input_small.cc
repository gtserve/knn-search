#include <gtest/gtest.h>
#include <vector>

#include "../input.h"

#define DATA_PATH "/home/gtserve/Code/k23a-project/data"

using namespace std;

TEST(InputSmallTest, ReadBaseVectors) {
    string data_path = DATA_PATH;
    vector<DataPoint<float>> data_points;
    readVectors<float> (data_path + "/siftsmall/siftsmall_base.fvecs", data_points);
    EXPECT_EQ(data_points.size(), 10000);
}

TEST(InputSmallTest, ReadQueryVectors) {
    string data_path = DATA_PATH;
    vector<DataPoint<float>> data_points;
    readVectors<float> (data_path + "/siftsmall/siftsmall_query.fvecs", data_points);
    EXPECT_EQ(data_points.size(), 100);
}

TEST(InputSmallTest, ReadLearnVectors) {
    string data_path = DATA_PATH;
    vector<DataPoint<float>> data_points;
    readVectors<float> (data_path + "/siftsmall/siftsmall_learn.fvecs", data_points);
    EXPECT_EQ(data_points.size(), 25000);
}

TEST(InputSmallTest, ReadGroundTruthVectors) {
    string data_path = DATA_PATH;
    vector<DataPoint<int>> data_points;
    readVectors<int> (data_path + "/siftsmall/siftsmall_groundtruth.ivecs", data_points);
    EXPECT_EQ(data_points.size(), 100);
}
