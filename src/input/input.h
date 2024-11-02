/*
* input.h
* --------------------------------------------------------------------------------
* Template function to read vectors from .fvecs, ivecs binary files.
* --------------------------------------------------------------------------------
* The vectors are stored in raw little endian. Each vector takes 4+d*4 bytes for
* .fvecs and .ivecs formats, where d is the dimensionality of the vector.
* --------------------------------------------------------------------------------
*/

#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <fstream>
#include <vector>

#include "../data_vectors/data_point.h"


template <typename T>
void readVectors(const std::string &file_name, std::vector<DataVector<T>>& data_vectors) {
    std::ifstream ifs(file_name, std::ios::binary);

    if (!ifs.is_open()) {
        std::cerr << "[ERROR]: Opening file: '" << file_name << "'" << std::endl;
        return;
    }

    while (ifs.good()) {
        // Read dimension of data points.
        int dimension;
        ifs.read(reinterpret_cast<char *>(&dimension), sizeof(int));
        if (!ifs) break;    // if EOF was read, break loop.

        std::vector<T> v(dimension);
        ifs.read(reinterpret_cast<char *>(v.data()), dimension * sizeof(T));
        DataVector<T> dv(v);
        data_vectors.push_back(dv);
    }
}

#endif //INPUT_H
