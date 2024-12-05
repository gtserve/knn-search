/*
* test_input_small.cc
* --------------------------------------------------------------------------------
* You can use this file to read from data set ANN_SIFT10K which can be found
* here: http://corpus-texmex.irisa.fr/
* --------------------------------------------------------------------------------
* You need to have the dataset already download and provide the directory path to
* the DATA_PATH macro.
* --------------------------------------------------------------------------------
*/


#include <gtest/gtest.h>
#include <vector>

#include "../input.h"

#define DATA_PATH ""

using namespace std;

TEST(InputSmallTest, ReadBaseVectors) {
    ASSERT_TRUE(DATA_PATH != "");
    string data_path = DATA_PATH;
    vector<vector<float>> vectors;
    readTexmexVectors<float> (data_path + "/siftsmall_base.fvecs", vectors);
    EXPECT_EQ(vectors.size(), 10000);
}

TEST(InputSmallTest, ReadQueryVectors) {
    ASSERT_TRUE(DATA_PATH != "");
    string data_path = DATA_PATH;
    vector<vector<float>> data_vectors;
    readTexmexVectors<float> (data_path + "/siftsmall_query.fvecs", data_vectors);
    EXPECT_EQ(data_vectors.size(), 100);
}

TEST(InputSmallTest, ReadLearnVectors) {
    ASSERT_TRUE(DATA_PATH != "");
    string data_path = DATA_PATH;
    vector<vector<float>> data_vectors;
    readTexmexVectors<float> (data_path + "/siftsmall_learn.fvecs", data_vectors);
    EXPECT_EQ(data_vectors.size(), 25000);
}

TEST(InputSmallTest, ReadGroundTruthVectors) {
    ASSERT_TRUE(DATA_PATH != "");
    string data_path = DATA_PATH;
    vector<vector<int>> data_vectors;
    readTexmexVectors<int> (data_path + "/siftsmall_groundtruth.ivecs", data_vectors);
    EXPECT_EQ(data_vectors.size(), 100);
}
