#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>

#include "input.h"

using namespace std;

template <typename T>
void writeVectorsToBinaryFile(const string& file_name, const vector<vector<T>>& vectors) {
    ofstream ofs(file_name, std::ios::binary);

    if (!ofs) {
        cerr << "[ERROR]: Could not open file for writing." << endl;;
        return;
    }

    // Write each vector's dimension and its elements.
    for (int i = 0; i < vectors.size(); i++) {
        // Write dimension of vector.
        int dimension = vectors[i].size();
        ofs.write(reinterpret_cast<const char*>(&dimension), sizeof(dimension));

        ofs.write(reinterpret_cast<const char*>(vectors[i].data()), dimension * sizeof(T));
    }

    ofs.close();
}

TEST(TestInput, EmptyVectorFile) {
    const vector<vector<int>> vectors_empty;
    const char* file_name = "./vector_empty.bin";

    writeVectorsToBinaryFile<int>(file_name, vectors_empty);

    // Read binary file.
    vector<vector<int>> vectors;
    readVectors<int> (file_name, vectors);

    // Delete binary file.
    if (remove(file_name) != 0) {
        cerr << "[ERROR]: Could not remove file: '" << file_name << "'" << endl;;
    }

    EXPECT_EQ(vectors.size(), 0);
}

TEST(TestInput, OneVectorFile) {
    const vector<vector<int>> vectors_1x1 = {{0}};
    const char* file_name = "./vector_1x1.bin";

    writeVectorsToBinaryFile<int>(file_name, vectors_1x1);

    // Read binary file.
    vector<vector<int>> data_vectors;
    readVectors<int> (file_name, data_vectors);

    // Delete binary file.
    if (remove(file_name) != 0) {
        cerr << "[ERROR]: Could not remove file: '" << file_name << "'" << endl;;
    }

    EXPECT_EQ(data_vectors.size(), 1);
}

TEST(TestInput, OneThreeVectorFile) {
    const vector<vector<int>> vectors_1x3 = {{1, 2, 3}};
    const char* file_name = "./vectors_1x3.bin";

    writeVectorsToBinaryFile<int>(file_name, vectors_1x3);

    // Read binary file.
    vector<vector<int>> data_vectors;
    readVectors<int> (file_name, data_vectors);

    // Delete binary file.
    if (remove(file_name) != 0) {
        cerr << "[ERROR]: Could not remove file: '" << file_name << "'" << endl;;
    }

    EXPECT_EQ(data_vectors.size(), 1);
}

TEST(TestInput, ThreeThreeVectorFile) {
    const vector<vector<int>> vectors_3x3 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    const char* file_name = "./vectors_3x3.bin";

    writeVectorsToBinaryFile<int>(file_name, vectors_3x3);

    // Read binary file.
    vector<vector<int>> data_vectors;
    readVectors<int> (file_name, data_vectors);

    // Delete binary file.
    if (remove(file_name) != 0) {
        cerr << "[ERROR]: Could not remove file: '" << file_name << "'" << endl;;
    }

    EXPECT_EQ(data_vectors.size(), 3);
}