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

    unordered_map<int, unordered_set<int> > node_filters;//map that stores what nodes are associated with which filter

    //unordered map for storing distances TEST TEST
    unordered_map<pair<int, int>, long double,PairHash> distances_map;

public:

    graph(const vector<vector<T>> &vectors,const int R); //initialise graph

    graph(const vector<vector<T> > &vectors); //initialise graph

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

    void add_node_filter(int f,int node);

    unordered_set<int> get_nodes_for_filter(int f);
};

//graph<T>::graph(const vector<vector<T> > &vectors) {
//initialize graph
template<typename T>
graph<T>::graph(const vector<vector<T> > &vectors)
{

    for (int i = 0; i < vectors.size(); i++) {
        auto *new_node = new vector_node<T>(i, vectors[i]);
        this->nodes.push_back(new_node);
        //neighbours[i].reserve(R);
    }
}


template<typename T>
graph<T>::graph(const vector<vector<T>> &vectors,const int R)
 {


    for (int i = 0; i < vectors.size(); i++) {
        auto *new_node = new vector_node<T>(i, vectors[i]);
        this->nodes.push_back(new_node);
        neighbours[i].reserve(R);
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

/*
template <typename T>
set<int> graph<T>::getNodeNeighbours(const int id)
*/

template <typename T>
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
long double graph<T>::getDistance(int x, int y)
{
    //auto it = this->distances_map.find({min(x,y),max(x,y)});
     if (this->distances_map.find({min(x,y),max(x,y)}) != this->distances_map.end())
     {
        return this->distances_map[{min(x,y),max(x,y)}];
     }
    return 0.0;
}

template<typename T>
void graph<T>::addDistance(int x, int y, long double distance)
{
    this->distances_map[{min(x,y),max(x,y)}]=distance;
}

template<typename T>
void graph<T>::add_node_filter(int f, int node)
{
    this->node_filters[f].insert(node);
}

template<typename T>
unordered_set<int> graph<T>::get_nodes_for_filter(int f)
{
    return this->node_filters[f];
}

// //add new vertice in vertice vector
// graph add_vector(int, list<int>);
//
// //function that takes file as argument and generates a random graph
// graph generate_random_graph(graph *, fstream &);
//
// //search graph to find the K closest neighbors of node with id->querry_id starting from node->starting with search size L
// set<pair<int, int>, compare_by_second_value> greedy_graph_search(graph *, vector_node *starting, vector_node querry,
//                                                                  int k, int L);
//
// //check a candidate set of nodes(vector candidates) to form new neighbors for node
// void robust_prune(graph *, vector_node *node, vector<vector_node *> candidates, int a, int R);
//
// void print_graph(graph);



#endif //GRAPH_VECTOR_H
