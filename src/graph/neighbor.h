//
// Created by Nikos Tsolkas on 21/10/2024.
//

#ifndef NEIGHBOR_H
#define NEIGHBOR_H

#include <list>

using namespace std;

class neighbor
{
    private:
        int node_id;
        list<int> instances;//list of vector instances
        int euclidean_distance;//euclidean distance of current neighbor node with vertice
    public:
        neighbor(int node_id, list<int> parent_instances, list<int> instances);
        int get_node_id();
        int get_distance();
        void add_neighbor(int node_id, list<int> parent_instances, list<int> instances);
};





#endif //NEIGHBOR_H
