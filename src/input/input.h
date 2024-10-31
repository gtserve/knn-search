/*
* input.h
* --------------------------------------------------------------------------------
* Functions to read vectors from .bvecs, .fvecs, ivecs binary files.
* --------------------------------------------------------------------------------
* The vectors are stored in raw little endian. Each vector takes 4+d*4 bytes for
* .fvecs and .ivecs formats, and 4+d bytes for .bvecs formats, where d is the
* dimensionality of the vector, as shown below.
* --------------------------------------------------------------------------------
*/

#ifndef INPUT_H
#define INPUT_H

bool hasSuffix(const std::string &str, const std::string &suffix);

void readFVectors(const std::string &fileName, std::vector<std::vector<float> > &vectors);

void readIVectors(const std::string &fileName, std::vector<std::vector<int> > &vectors);

void readBVectors(const std::string &fileName, std::vector<std::vector<char> > &vectors);

#endif //INPUT_H
