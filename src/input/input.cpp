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
    vector<std::vector<float> > &data
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

    data.resize(N);
    for (auto &row: data)
        row.resize(vec_dimension + num_attributes);

    // Read vectors.
    for (int i = 0; i < N; i++)
        ifs.read(reinterpret_cast<char *>(data[i].data()), (vec_dimension + num_attributes) * sizeof(float));

    if (queries) {
        // Erase queries of type 2 and 3.
        for (auto it = data.begin(); it != data.end();) {
            if ((*it)[0] == 2 || (*it)[0] == 3)
                it = data.erase(it);
            else
                ++it;
        }
    }

    ifs.close();
    std::cout << "Done!" << std::endl;
}
