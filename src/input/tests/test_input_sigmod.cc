#include <gtest/gtest.h>
#include <input.h>

#define DATA_PATH "../../../../data/sigmod"
#define DIMENSION 100

using namespace std;

TEST(TestInputSigmod, DataVectors) {
    vector<vector<float>> data_vectors;
    string data_path = DATA_PATH;
    readSigmodVectors(data_path + "/dummy-data.bin", DIMENSION, 2, false, data_vectors);
    EXPECT_EQ(data_vectors.size(), 10000);
}

TEST(TestInputSigmod, DataQueries) {
    vector<vector<float>> data_queries;
    string data_path = DATA_PATH;
    readSigmodVectors(data_path + "/dummy-queries.bin", DIMENSION, 4, true, data_queries);
    cout << data_queries.size() << endl;
}
