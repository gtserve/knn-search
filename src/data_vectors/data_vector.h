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
#include <utility_functions.h>

template <typename T>
class DataVector {
    std::vector<T> data;

public:
    explicit DataVector(const std::vector<T> data);
    int getSize() const;
    double getDistance(DataVector<T>* target) const;
};

template <typename T>
DataVector<T>::DataVector(const std::vector<T> data)
	: data(data) {}

template <typename T>
int DataVector<T>::getSize() const {
	return data.size();
}

template<typename T>
double DataVector<T>::getDistance(DataVector<T> *target) const {
    return euclidean_distance(data, target->data);
}


#endif //DATA_VECTOR_H
