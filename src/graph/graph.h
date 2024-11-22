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

#include <vector_node.h>


template<typename T>
class graph {
private:
    vector<vector_node<T> *> nodes; //vector that stores alla vertices
    map<int, set<int> > neighbours; // Adjacency List

public:
    graph(const vector<vector<T> > &vectors); //initialise graph
    ~graph();

    void generate_random_graph(const int R);

    void print();

    int get_vertices(); //return number of vertices in graph
    vector_node<T> *get_node(int);

    set<int> getNodeNeighbours(int id);

    void addEdgeDirected(int u, int v);

    void deleteEdgeDirected(int u, int v);

    void clearNeighbours(int id);
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
set<int> graph<T>::getNodeNeighbours(const int id) {
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


#endif //GRAPH_VECTOR_H
