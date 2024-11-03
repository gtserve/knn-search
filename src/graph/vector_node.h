//
// Created by Nikos Tsolkas on 21/10/2024.
//

#ifndef VECTOR_NODE_H
#define VECTOR_NODE_H


#include <list>
#include <vector>
#include <set>
#include "neighbor.h"

#include "../utility/utility_functions.h"

using namespace std;

class vector_node
{
    private:
        int node_id;
        list<int> coordinates;//list of vector instances
        set<pair<vector_node*,int>> neighbors;
        //vector<neighbor> neighbors;//vector that stores nodes neighbors
    public:
        vector_node(int node_id,list<int> coordinates); //create node
        int get_node_id();
        list<int> get_coordinates();
        int get_neighbors_size();
        vector<vector_node*> get_neighbors_list();
        void add_neighbor(vector_node*);
        void delete_neighbor(vector_node*);
};



#endif //VECTOR_NODE_H
