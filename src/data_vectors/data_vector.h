/*
* data_vector.h
* --------------------------------------------------------------------------------
* A class that represents a data point comprised of components of unknown size.
* --------------------------------------------------------------------------------
* The class is implemented as a template to accomodate components of different
* types. Implementations are defined here to avoid linker issues with cmake.
* --------------------------------------------------------------------------------
*/

#ifndef DATA_VECTOR_H
#define DATA_VECTOR_H


#include <vector>

template <typename T>
class DataVector {
    std::vector<T> data;

public:
    explicit DataVector(const std::vector<T>& data);
    int getSize() const;
};

template <typename T>
DataVector<T>::DataVector(const std::vector<T>& data)
	: data(data) {}

template <typename T>
int DataVector<T>::getSize() const {
	return data.size();
}


#endif //DATA_VECTOR_H
