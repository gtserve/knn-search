/*
* data_point.h
* --------------------------------------------------------------------------------
* A class that represents a data point comprised of components of unknown size.
* --------------------------------------------------------------------------------
* The class is implemented as a template to accomodate components of different
* types. Implementations are defined here to avoid linker issues with cmake.
* --------------------------------------------------------------------------------
*/

#ifndef DATA_POINT_H
#define DATA_POINT_H


#include <vector>

template <typename T>
class DataPoint {
    std::vector<T> components;

public:
    explicit DataPoint(const std::vector<T>& components);
    int getSize() const;
};

template <typename T>
DataPoint<T>::DataPoint(const std::vector<T>& components)
	: components(components) {}

template <typename T>
int DataPoint<T>::getSize() const {
	return components.size();
}


#endif //DATA_POINT_H
