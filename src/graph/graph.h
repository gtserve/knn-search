//
// Created by Nikos Tsolkas on 20/10/2024.
//

#ifndef GRAPH_VECTOR_H
#define GRAPH_VECTOR_H

#include <cstdlib>
#include <vector>
#include <set>
#include <cwchar>
#include <fstream>
#include <map>


#include "vector_node.h"
#include <data_vector.h>
#include <unordered_set>
#include <unordered_map>

#include <vector_node.h>


template<typename T>
class graph {
private:
    vector<vector_node<T> *> nodes; //vector that stores alla vertices

    map<int, unordered_set<int> > neighbours; // Adjacency List

    unordered_map<float, unordered_set<int> > nodes_with_filter;
    //map that stores what nodes are associated with which filter

    //unordered map for storing distances TEST TEST
    unordered_map<pair<int, int>, long double, PairHash> distances_map;

    set<float> total_filters;

public:
    graph(const vector<vector<T> > &vectors, const int R); //initialise graph

    graph(const vector<vector<T> > &vectors); //initialise graph

    graph(const vector<vector<T> > &vectors, const int R, const vector<vector<float> > &filters); //initialise graph

    ~graph();

    void generate_random_graph(const int R);

    void print();

    int get_vertices(); //return number of vertices in graph
    vector_node<T> *get_node(int);

    unordered_set<int> getNodeNeighbours(int id);

    void addEdgeDirected(int u, int v);

    void deleteEdgeDirected(int u, int v);

    void clearNeighbours(int id);


    //testing new unordered map for storing distances
    long double getDistance(int x, int y);

    void addDistance(int x, int y, long double distance);

    void add_node_filter(int f, int node);

    unordered_set<int> get_nodes_for_filter(int f);

    unordered_map<float, int> findMedoids(const int threshold);
};

//initialize graph
template<typename T>
graph<T>::graph(const vector<vector<T> > &vectors) {
    for (int i = 0; i < vectors.size(); i++) {
        auto *new_node = new vector_node<T>(i, vectors[i]);
        this->nodes.push_back(new_node);
    }
}

template<typename T>
graph<T>::graph(const vector<vector<T> > &vectors, const int R) {
    for (int i = 0; i < vectors.size(); i++) {
        auto *new_node = new vector_node<T>(i, vectors[i]);
        this->nodes.push_back(new_node);
        neighbours[i].reserve(R);
    }
}

template<typename T>
graph<T>::graph(const vector<vector<T> > &vectors, const int R, const vector<vector<float> > &filters) {
    for (int i = 0; i < vectors.size(); i++) {
        auto *new_node = new vector_node<T>(i, vectors[i], filters[i]);
        this->nodes.push_back(new_node);
        neighbours[i].reserve(R);

        for (const auto &filter: filters) {
            this->nodes_with_filter[filter].insert(i);
            this->total_filters.insert(filter);
        }
    }
}

template<typename T>
graph<T>::~graph() {
    for (int i = 0; i < this->nodes.size(); i++) {
        delete(this->nodes[i]);
    }
}

template<typename T>
void graph<T>::generate_random_graph(const int R) {
    srand(time(NULL));

    for (int i = 0; i < this->nodes.size(); i++) {
        while (this->neighbours[i].size() < R) {
            //find random node in graph to be connected to i
            int cur_neighbor = rand() % this->nodes.size();
            if (cur_neighbor != i)
                this->neighbours[i].insert(cur_neighbor);
        }
    }
}

template<typename T>
int graph<T>::get_vertices() {
    return this->nodes.size();
}

template<typename T>
vector_node<T> *graph<T>::get_node(int id) {
    return this->nodes[id];
}

template<typename T>
unordered_set<int> graph<T>::getNodeNeighbours(const int id) {
    return this->neighbours[id];
}

template<typename T>
void graph<T>::print() {
    for (const auto &pair: this->neighbours) {
        cout << "N[" << pair.first << "] ->";
        for (const auto &neighbour: pair.second) {
            cout << " N[" << neighbour << "]";
        }
        cout << endl;
    }
}

template<typename T>
void graph<T>::addEdgeDirected(const int u, const int v) {
    this->neighbours[u].insert(v);
}

template<typename T>
void graph<T>::deleteEdgeDirected(const int u, const int v) {
    this->neighbours[u].erase(v);
}

template<typename T>
void graph<T>::clearNeighbours(const int id) {
    this->neighbours[id].clear();
}

template<typename T>
long double graph<T>::getDistance(int x, int y) {
    if (x == y)
        return 0.0;

    int a = min(x, y);
    int b = max(x, y);

    long double dist = distances_map[{a, b}];
    if (dist == 0.0) {
        vector_node<T> *Na = this->get_node(a);
        vector_node<T> *Nb = this->get_node(b);
        dist = Na.getDistance(Nb);
        distances_map[{a, b}] = dist;
    }
    return dist;
}

template<typename T>
void graph<T>::addDistance(int x, int y, long double distance) {
    this->distances_map[{min(x, y), max(x, y)}] = distance;
}

template<typename T>
void graph<T>::add_node_filter(int f, int node) {
    this->nodes_with_filter[f].insert(node);
}

template<typename T>
unordered_set<int> graph<T>::get_nodes_for_filter(int f) {
    return this->nodes_with_filter[f];
}

template <typename T>
unordered_map<float, int> graph<T>::findMedoids(const int threshold) {
    unordered_map<float, int> m;
    unordered_map<int, int> t;

    for (const auto &f: this->total_filters) {

        srand(time(NULL));
        unordered_set<int> Rf;
        std::vector<int> setVector(this->nodes_with_filter[f].begin(), this->nodes_with_filter[f].end());

        while (Rf.size() < threshold) {
            int rand_index = rand() % this->nodes_with_filter[f].size();
            Rf.insert(setVector[rand_index]);
        }

        int min_count = 1e6;
        int min_node_id = -1;
        for (const auto &node_id: Rf) {
            if (t[node_id] < min_count) {
                min_node_id = node_id;
                min_count = t[node_id];
            }
        }

        m[f] = min_node_id;
        t[min_node_id] += 1;
    }
}


#endif //GRAPH_VECTOR_H
