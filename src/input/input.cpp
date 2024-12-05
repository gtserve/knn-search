/*
* input.cpp
* --------------------------------------------------------------------------------
* Template function to read vectors from .fvecs, ivecs binary files.
* --------------------------------------------------------------------------------
* The vectors are stored in raw little endian. Each vector takes 4+d*4 bytes for
* .fvecs and .ivecs formats, where d is the dimensionality of the vector.
* --------------------------------------------------------------------------------
*/

#include "input.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;


void readSigmodVectors(
    const string &file_path,
    const int num_attributes,
    const int vec_dimension,
    const bool queries,
    vector<std::vector<float> > &vectors,
    vector<vector<float>> &filters
) {
    std::cout << "Reading Data from: " << file_path << std::endl;
    std::ifstream ifs(file_path, std::ios::binary);

    if (!ifs.is_open()) {
        std::cerr << "[ERROR]: Opening file: '" << file_path << "'" << std::endl;
        return;
    }

    // Read number of data points / vectors.
    uint32_t N;
    ifs.read(reinterpret_cast<char *>(&N), sizeof(uint32_t));
    std::cout << "Reading " << N << " vectors ... " << std::endl;

    for (int i = 0; i < N; i++) {
        if (queries) {
            float query_type;
            ifs.read(reinterpret_cast<char *>(&query_type), sizeof(float));

            if (query_type == 2 || query_type == 3) {
                ifs.seekg(sizeof(float) * (vec_dimension + num_attributes - 1), ifs.cur);
                continue;
            }

            if (query_type == 0) {
                ifs.seekg(sizeof(float) * 3, ifs.cur);
                vector<float> fs = {-1};
                filters.push_back(fs);
            }

            if (query_type == 1) {
                float temp;
                ifs.read(reinterpret_cast<char *>(&temp), sizeof(float));
                vector<float> fs = {temp};
                filters.push_back(fs);
                ifs.seekg(sizeof(float) * 2, ifs.cur);
            }
        } else {
            // Read filter.
            float temp;
            ifs.read(reinterpret_cast<char *>(&temp), sizeof(float));
            vector<float> fs = {temp};
            filters.push_back(fs);
            // Ignore timestamp.
            ifs.seekg(sizeof(float), ifs.cur);
        }

        // Read vector.
        vector<float> temp(vec_dimension);
        ifs.read(reinterpret_cast<char *>(temp.data()), vec_dimension * sizeof(float));
        vectors.push_back(temp);
    }

    ifs.close();
    std::cout << "Done!" << std::endl;
}
