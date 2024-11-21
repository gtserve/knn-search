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
    std::vector<T> components;

public:
    explicit DataVector(std::vector<T> &components);
    int getSize() const;
    std::vector<T> getComponents() const;
    double getDistance(DataVector<T>* other) const;
    double getDistance(vector<T> &other) const;
};

template <typename T>
DataVector<T>::DataVector(std::vector<T> &components)
	: components(components) {}

template <typename T>
int DataVector<T>::getSize() const {
	return this->components.size();
}

template <typename T>
std::vector<T> DataVector<T>::getComponents() const {
    return this->components;
}

template<typename T>
double DataVector<T>::getDistance(DataVector<T> *other) const {
    return squared_euclidean_distance(this->components, other->getComponents());
}

template<typename T>
double DataVector<T>::getDistance(vector<T> &other) const {
    return squared_euclidean_distance(this->components, other);
}


#endif //DATA_VECTOR_H
