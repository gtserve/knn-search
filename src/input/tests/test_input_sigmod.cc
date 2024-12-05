#include <gtest/gtest.h>
#include <input.h>

#define DATA_PATH "../../../../data/sigmod"
#define DIMENSION 100

using namespace std;

TEST(TestInputSigmod, DataVectors) {
    vector<vector<float>> data_vectors;
    vector<vector<float>> filters;
    string data_path = DATA_PATH;
    readSigmodVectors(data_path + "/dummy-data.bin", 2, DIMENSION, false, data_vectors, filters);

    for (int i = 0; i < 10; i++) {
        cout << "[" << filters[i][0] << "] ";
        for (int j = 0; j < data_vectors[i].size(); j++) {
            cout << data_vectors[i][j] << ", ";
        }
        cout << "\b\b" << endl;
    }
    cout << endl;

    EXPECT_EQ(data_vectors.size(), 10000);
}

TEST(TestInputSigmod, DataQueries) {
    vector<vector<float>> data_queries;
    vector<vector<float>> filters;
    string data_path = DATA_PATH;
    readSigmodVectors(data_path + "/dummy-queries.bin", 4, DIMENSION, true, data_queries, filters);

    for (int i = 0; i < 10; i++) {
        cout << "[" << filters[i][0] << "] ";
        for (int j = 0; j < data_queries[i].size(); j++) {
            cout << data_queries[i][j] << ", ";
        }
        cout << "\b\b" << endl;
    }
    cout << endl;

    cout << data_queries.size() << endl;
}
