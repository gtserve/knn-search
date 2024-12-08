#include <gtest/gtest.h>
#include <input.h>

#define DATA_PATH "../../../../data/sigmod"
#define DIMENSION 100

using namespace std;

TEST(TestInputSigmod, DataVectors) {
    vector<vector<float> > data_vectors;
    vector<set<float> > filters;
    string data_path = DATA_PATH;
    readSigmodVectors(data_path + "/dummy-data.bin", DIMENSION, false, data_vectors, filters);

    for (int i = 0; i < 10; i++) {
        for (const auto &f: filters[i])
            cout << "[" << f << ", ";
        cout << "\b\b] ";

        for (const auto &x : data_vectors[i])
            cout << x << ", ";
        cout << "\b\b" << endl;
    }
    cout << endl;

    EXPECT_EQ(data_vectors.size(), 10000);
}

TEST(TestInputSigmod, DataQueries) {
    vector<vector<float> > data_queries;
    vector<set<float> > filters;
    string data_path = DATA_PATH;
    readSigmodVectors(data_path + "/dummy-queries.bin", DIMENSION, true, data_queries, filters);

    for (int i = 0; i < 10; i++) {
        for (const auto &f: filters[i])
            cout << "[" << f << ", ";
        cout << "\b\b] ";

        for (const auto &x : data_queries[i])
            cout << x << ", ";
        cout << "\b\b" << endl;
    }
    cout << endl;

    cout << data_queries.size() << endl;
}

TEST(TestSigmod, GroundTruth) {
    string data_path = DATA_PATH;
    generateSigmodGroundTruthFile(
        data_path + "/dummy-data.bin",
        data_path + "/dummy-queries.bin",
        data_path + "/dummy-groundtruth.bin",
        100
    );

    vector<vector<int> > ground_truth;
    readSigmodGroundTruth(data_path + "/dummy-groundtruth.bin", ground_truth);

    for (int i = 0; i < ground_truth.size(); i++) {
        cout << "q[" << i << "]: ";
        for (int j = 0; j < ground_truth[i].size(); j++) {
            cout << ground_truth[i][j] << ", ";
        }
        cout << "\b\b" << endl;
    }
    cout << endl;
}
