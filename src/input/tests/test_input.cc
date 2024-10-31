#include <gtest/gtest.h>
#include <vector>

#include "../input.h"

#define DATA_PATH "/home/gtserve/Code/k23a-project/data"

using namespace std;

TEST(InputSmall, BaseVectors) {
    string data_path = DATA_PATH;
    vector<vector<float> > vectors;
    readFVectors(data_path + "/siftsmall/siftsmall_base.fvecs", vectors);
    EXPECT_EQ(vectors.size(), 10000);
}

TEST(InputSmall, QueryVectors) {
    string data_path = DATA_PATH;
    vector<vector<float> > vectors;
    readFVectors(data_path + "/siftsmall/siftsmall_query.fvecs", vectors);
    EXPECT_EQ(vectors.size(), 100);
}

TEST(InputSmall, LearnVectors) {
    string data_path = DATA_PATH;
    vector<vector<float> > vectors;
    readFVectors(data_path + "/siftsmall/siftsmall_learn.fvecs", vectors);
    EXPECT_EQ(vectors.size(), 25000);
}

TEST(InputSmall, GroundTruthVectors) {
    string data_path = DATA_PATH;
    vector<vector<int> > vectors;
    readIVectors(data_path + "/siftsmall/siftsmall_groundtruth.ivecs", vectors);
    EXPECT_EQ(vectors.size(), 100);
}
