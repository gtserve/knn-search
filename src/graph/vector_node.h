//
// Created by Nikos Tsolkas on 21/10/2024.
//

#ifndef VECTOR_NODE_H
#define VECTOR_NODE_H

#include <vector>
#include <data_vector.h>


template<typename T>
class vector_node {
private:
    int node_id;
    DataVector<T> *data_vector;

public:
    vector_node(const int node_id, vector<T> components); //create node

    ~vector_node();

    int get_node_id();

    DataVector<T>* get_coordinates();

    double getDistance(vector_node<T>* other);

    double getDistance(vector<T> &other);

    set<int> getFilters() const;
};

template<typename T>
vector_node<T>::vector_node(const int node_id, vector<T> components) {
    this->node_id = node_id;
    this->data_vector = new DataVector<T>(components);
}

template<typename T>
vector_node<T>::~vector_node() {
    delete(this->data_vector);
}

template<typename T>
int vector_node<T>::vector_node::get_node_id() {
    return this->node_id;
}

template <typename T>
DataVector<T>* vector_node<T>::vector_node::get_coordinates() {
    return this->data_vector;
}

template<typename T>
double vector_node<T>::getDistance(vector_node<T> *other) {
    return this->data_vector->getDistance(other->get_coordinates());
}

template<typename T>
double vector_node<T>::getDistance(vector<T> &other) {
    return this->data_vector->getDistance(other);
}

template<typename T>
set<int> vector_node<T>::getFilters() const {
    return this->data_vector->getFilters();
}


#endif //VECTOR_NODE_H
