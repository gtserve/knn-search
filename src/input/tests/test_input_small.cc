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

#define DATA_PATH "/home/blah/.../blah/siftsmall"

using namespace std;

TEST(InputSmallTest, ReadBaseVectors) {
    string data_path = DATA_PATH;
    vector<DataVector<float>> data_vectors;
    readVectors<float> (data_path + "/siftsmall_base.fvecs", data_vectors);
    EXPECT_EQ(data_vectors.size(), 10000);
}

TEST(InputSmallTest, ReadQueryVectors) {
    string data_path = DATA_PATH;
    vector<DataVector<float>> data_vectors;
    readVectors<float> (data_path + "/siftsmall_query.fvecs", data_vectors);
    EXPECT_EQ(data_vectors.size(), 100);
}

TEST(InputSmallTest, ReadLearnVectors) {
    string data_path = DATA_PATH;
    vector<DataVector<float>> data_vectors;
    readVectors<float> (data_path + "/siftsmall_learn.fvecs", data_vectors);
    EXPECT_EQ(data_vectors.size(), 25000);
}

TEST(InputSmallTest, ReadGroundTruthVectors) {
    string data_path = DATA_PATH;
    vector<DataVector<int>> data_vectors;
    readVectors<int> (data_path + "/siftsmall_groundtruth.ivecs", data_vectors);
    EXPECT_EQ(data_vectors.size(), 100);
}
