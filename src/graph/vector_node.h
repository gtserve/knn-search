//
// Created by Nikos Tsolkas on 21/10/2024.
//

#ifndef VECTOR_NODE_H
#define VECTOR_NODE_H


#include <list>
#include <vector>
#include "neighbor.h"

using namespace std;

class vector_node
{
    private:
        int node_id;
        list<int> coordinates;//list of vector instances
        vector<neighbor> neighbors;//vector that stores nodes neighbors
    public:
        vector_node(int node_id,list<int> coordinates); //create node
        int get_node_id();
        list<int> get_coordinates();
        void add_neighbor(neighbor n);
        void delete_neighbor(neighbor n);
};



#endif //VECTOR_NODE_H
