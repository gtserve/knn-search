//
// Created by Nikos Tsolkas on 20/10/2024.
//

#ifndef GRAPH_VECTOR_H
#define GRAPH_VECTOR_H

#include <cstdlib>
#include <vector>
#include <cwchar>
#include <fstream>

#include "vector_node.h"

#define NEIGHBOR 1000

using namespace std;

class graph
{
    private:
        int vertices;
        vector<vector_node> vertices_array;//vector that stores alla vertices
    public:
        graph();//initialise graph
        void add_vector(int,list<int>); // add new vector to list of vertices
        void add_neighbor_to_vector(int,neighbor);
        void print_graph();
        int get_vertices(); //return number of vertices in graph
        vector_node get_vector(int);
};

//add new vertice in vertice vector
graph add_vector(int,list<int>);

//function that takes file as argument and generates a random graph
graph generate_random_graph(graph*, fstream &);

void print_graph(graph);
#endif //GRAPH_VECTOR_H
