//
// Created by Nikos Tsolkas on 21/10/2024.
//

#ifndef VECTOR_NODE_H
#define VECTOR_NODE_H


#include <list>
#include <vector>
#include <set>
#include <data_vector.h>

#include "neighbor.h"

#include "../utility/utility_functions.h"

using namespace std;

template<typename T>
class vector_node {
private:
    int node_id;
    DataVector<T> *data_vector;
    set<pair<vector_node *, int> > neighbors;
    //vector<neighbor> neighbors;//vector that stores nodes neighbors
public:
    vector_node(const int node_id, DataVector<T> *data_vector); //create node

    int get_node_id();

    DataVector<T>* get_coordinates();

    double getDistance(vector_node<T>* other);

    // int get_neighbors_size();
    //
    // vector<vector_node *> get_neighbors_list();
    //
    // void add_neighbor(vector_node *);
    //
    // void delete_neighbor(vector_node *);
};

template<typename T>
vector_node<T>::vector_node(const int node_id, DataVector<T> *data_vector) {
    this->node_id = node_id;
    this->data_vector = data_vector;
}

template<typename T>
int vector_node<T>::vector_node::get_node_id() {
    return this->node_id;
}

template <typename T>
DataVector<T>* vector_node<T>::vector_node::get_coordinates()
{
    return this->data_vector;
}

template<typename T>
double vector_node<T>::getDistance(vector_node<T> *other) {
    return this->data_vector->getDistance(other->get_coordinates());
}


// template<typename T>
// int vector_node<T>::vector_node::get_neighbors_size()
// {
//     return this->neighbors.size();
// }
//
// template<typename T>
// vector<vector_node*> vector_node<T>::vector_node::get_neighbors_list()
// {
//     vector<vector_node*> neighbors_list;
//     auto it = this->neighbors.begin();
//     while(it != this->neighbors.end())
//     {
//         neighbors_list.push_back(it->first);
//         it++;
//     }
//
//     return neighbors_list;
// }
//
// template<typename T>
// void vector_node<T>::vector_node::add_neighbor(vector_node* n)
// {
//     this->neighbors.insert(make_pair(n,euclidean_distance(this->get_coordinates(),n->get_coordinates())));
// }
//
// template<typename T>
// void vector_node<T>::vector_node::delete_neighbor(vector_node* n)
// {
//     /*for(int i = 0; i < this->neighbors.size(); i++)
//     {
//         if(this->neighbors[i].get_node_id() == n.get_node_id())
//         {
//                 neighbors.erase(neighbors.begin() + i);
//         }
//     }
//     return;
//     */
//     auto it = this->neighbors.begin();
//     while(it != this->neighbors.end())
//     {
//         if(it->first == n)
//         {
//             this->neighbors.erase(it);
//             return;
//         }
//         it++;
//     }
// }


#endif //VECTOR_NODE_H
