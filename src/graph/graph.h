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


#define NEIGHBOR 1000

using namespace std;

template<typename T>
class graph {
private:
    vector<vector_node<T> *> nodes; //vector that stores alla vertices
    map<int, set<int> > neighbours; // Adjacency List

public:
    graph(const vector<DataVector<T> *> vectors); //initialise graph
    ~graph();

    // void add_node(int,list<int>); // add new vector to list of vertices
    //void add_neighbor_to_vector(int,neighbor);
    void generate_random_graph(const int R);

    void print_graph();

    int get_vertices(); //return number of vertices in graph
    vector_node<T> *get_node(int);

    set<int> getNodeNeighbours(int id);
};

//initialize graph
template<typename T>
graph<T>::graph(const vector<DataVector<T> *> vectors) {
    for (int i = 0; i < vectors.size(); i++) {
        auto *new_node = new vector_node<T>(i, vectors[i]);
        this->nodes.push_back(new_node);
    }
}

template<typename T>
graph<T>::~graph() {
    for (int i = 0; i < this->nodes.size(); i++) {
        delete(nodes[i]);
    }
}


// void graph::add_node(int id, list<int> coordinates)
// {
//     //creating a temp node to add to graph
//     vector_node temp(id,coordinates);
//
//     this->vertices++;
//     this->nodes.push_back(temp);
// }


/*void graph::add_neighbor_to_vector(int node, neighbor n)
{
    this->vertices_array[node].add_neighbor(n);
}
 */

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

template <typename T>
set<int> graph<T>::getNodeNeighbours(const int id) {
    return this->neighbours[id];
}

template<typename T>
void graph<T>::print_graph() {
    for (const auto &pair : this->neighbours) {
        cout << "N[" << pair.first << "] ->";
        for (const auto &neighbour : pair.second) {
            cout << " N[" << neighbour << "]";
        }
        cout << endl;
    }
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
