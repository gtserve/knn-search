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


void readSigmodVectors(
    const std::string &file_path,
    int num_attributes,
    int vec_dimension,
    bool queries,
    std::vector<std::vector<float> > &data,
    std::vector<std::vector<float> > &filters
);

template<typename T>
void readTexmexVectors(const std::string &file_name, std::vector<std::vector<T> > &vectors) {
    std::ifstream ifs(file_name, std::ios::binary);

    if (!ifs.is_open()) {
        std::cerr << "[ERROR]: Opening file: '" << file_name << "'" << std::endl;
        return;
    }

    while (ifs.good()) {
        // Read dimension of data points.
        int dimension;
        ifs.read(reinterpret_cast<char *>(&dimension), sizeof(int));
        if (!ifs) break; // if EOF was read, break loop.

        std::vector<T> v(dimension);
        ifs.read(reinterpret_cast<char *>(v.data()), dimension * sizeof(T));
        vectors.push_back(v);
    }
}

#endif //INPUT_H
