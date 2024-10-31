/*
* input.cpp
* --------------------------------------------------------------------------------
* Functions to read vectors from .bvecs, .fvecs, ivecs binary files.
* --------------------------------------------------------------------------------
* The vectors are stored in raw little endian. Each vector takes 4+d*4 bytes for
* .fvecs and .ivecs formats, and 4+d bytes for .bvecs formats, where d is the
* dimensionality of the vector, as shown below.
* --------------------------------------------------------------------------------
*/


#include <iostream>
#include <fstream>
#include <vector>

#include "input.h"


using namespace std;


bool hasSuffix(const std::string &str, const std::string &suffix) {
    if (suffix.length() > str.length()) {
        return false;
    }
    return str.compare((str.length() - suffix.length()), suffix.length(), suffix) == 0;
}

void readFVectors(const string &fileName, vector<vector<float>> &vectors) {
    std::ifstream ifs(fileName, std::ios::binary);

    if (!ifs.is_open()) {
        cout << "Error opening file " << fileName << endl;
        return;
    }

    // Each vector: 4 + d*4 bytes
    while (ifs) {
        int dimension;
        ifs.read(reinterpret_cast<char *>(&dimension), sizeof(int));
        if (!ifs) break;
        vector<float> vec(dimension);
        ifs.read(reinterpret_cast<char *>(vec.data()), dimension * sizeof(float));
        vectors.push_back(vec);
    }
}

void readIVectors(const string &fileName, vector<vector<int>> &vectors) {
    std::ifstream ifs(fileName, std::ios::binary);

    if (!ifs.is_open()) {
        cout << "Error opening file " << fileName << endl;
        return;
    }

    // Each vector: 4 + d*4 bytes
    while (ifs) {
        int dimension;
        ifs.read(reinterpret_cast<char *>(&dimension), sizeof(int));
        if (!ifs) break;
        vector<int> vec(dimension);
        ifs.read(reinterpret_cast<char *>(vec.data()), dimension * sizeof(int));
        vectors.push_back(vec);
    }
}

void readBVectors(const string &fileName, vector<vector<char>> &vectors) {
    std::ifstream ifs(fileName, std::ios::binary);

    if (!ifs.is_open()) {
        cout << "Error opening file " << fileName << endl;
        return;
    }

    // Each vector: 4 + d bytes
    while (ifs) {
        int dimension;
        ifs.read(reinterpret_cast<char *>(&dimension), sizeof(int));
        if (!ifs) break;
        vector<char> vec(dimension);
        ifs.read(reinterpret_cast<char *>(vec.data()), dimension * sizeof(char));
        vectors.push_back(vec);
    }
}
