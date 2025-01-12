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

template<typename T>
class DataVector {
    std::vector<T> components;
    std::set<float> filters;

public:
    explicit DataVector(const std::vector<T> &components);

    explicit DataVector(const std::vector<T> &components, const std::set<float> &filters);

    int getSize() const;

    std::vector<T> getComponents() const;

    std::set<float> getFilters() const;

    double getDistance(DataVector<T> *other) const;

    double getDistance(vector<T> &other) const;

    void print();

    void addFilter(const float &filter);
};

template<typename T>
DataVector<T>::DataVector(const std::vector<T> &components)
    : components(components) {
}

template<typename T>
DataVector<T>::DataVector(const std::vector<T> &components, const std::set<float> &filters)
    : components(components), filters(filters) {
}

template<typename T>
int DataVector<T>::getSize() const {
    return this->components.size();
}

template<typename T>
std::vector<T> DataVector<T>::getComponents() const {
    return this->components;
}

template<typename T>
std::set<float> DataVector<T>::getFilters() const {
    return this->filters;
}

template<typename T>
double DataVector<T>::getDistance(DataVector<T> *other) const {
    return euclidean_distance(this->components, other->getComponents());
}

template<typename T>
double DataVector<T>::getDistance(vector<T> &other) const {
    return euclidean_distance(this->components, other);
}

template<typename T>
void DataVector<T>::print() {
    if (!filters.empty()) {
        std::cout << "[";
        for (const auto &filter: this->filters)
            std::cout << filter << " ";
        std::cout << "\b] ";
    }

    for (const auto &component: this->components)
        std::cout << component << ", ";
    std::cout << "\b\b" << std::endl;
}


#endif //DATA_VECTOR_H
