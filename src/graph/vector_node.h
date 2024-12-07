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
    vector_node(const int node_id, const vector<T> &components); //create node

    vector_node(const int node_id, const vector<T> &components, const set<float> &filters); //create node

    ~vector_node();

    int get_node_id() const;

    vector<T> getComponents() const;

    double getDistance(vector_node<T>* other) const;

    double getDistance(vector<T> &other) const;

    set<float> getFilters() const;

    void addFilter(const float &filter);
};

template<typename T>
vector_node<T>::vector_node(const int node_id, const vector<T> &components) {
    this->node_id = node_id;
    this->data_vector = new DataVector<T>(components);
}

template<typename T>
vector_node<T>::vector_node(const int node_id, const vector<T> &components, const set<float> &filters) {
    this->node_id = node_id;
    this->data_vector = new DataVector<T>(components, filters);
}

template<typename T>
vector_node<T>::~vector_node() {
    delete(this->data_vector);
}

template<typename T>
int vector_node<T>::vector_node::get_node_id() const {
    return this->node_id;
}

template <typename T>
vector<T> vector_node<T>::vector_node::getComponents() const {
    return this->data_vector->getComponents();
}

template<typename T>
double vector_node<T>::getDistance(vector_node<T> *other) const {
    vector<T> other_comp = other->getComponents();
    return this->data_vector->getDistance(other_comp);
}

template<typename T>
double vector_node<T>::getDistance(vector<T> &other) const {
    return this->data_vector->getDistance(other);
}

template<typename T>
set<float> vector_node<T>::getFilters() const {
    return this->data_vector->getFilters();
}

template <typename T>
void vector_node<T>::addFilter(const float &filter) {
    this->data_vector->addFilter(filter);
}

#endif //VECTOR_NODE_H
