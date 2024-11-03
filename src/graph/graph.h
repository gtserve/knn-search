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

#include "vector_node.h"


#define NEIGHBOR 1000

using namespace std;

class graph
{
    private:
        int vertices;
        vector<vector_node> nodes;//vector that stores alla vertices
    public:
        graph();//initialise graph
        void add_node(int,list<int>); // add new vector to list of vertices
        //void add_neighbor_to_vector(int,neighbor);
        void print_graph();
        int get_vertices(); //return number of vertices in graph
        vector_node *get_node(int);
};

//add new vertice in vertice vector
graph add_vector(int,list<int>);

//function that takes file as argument and generates a random graph
graph generate_random_graph(graph*, fstream &);

//search graph to find the K closest neighbors of node with id->querry_id starting from node->starting with search size L
set<pair<int,int>,compare_by_second_value> greedy_graph_search(graph*,vector_node *starting,vector_node querry, int k,int L);

//check a candidate set of nodes(vector candidates) to form new neighbors for node
void robust_prune(graph*,vector_node *node,vector<vector_node*> candidates, int a,int R);

void print_graph(graph);
#endif //GRAPH_VECTOR_H
