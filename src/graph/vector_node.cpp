//
// Created by Nikos Tsolkas on 21/10/2024.
//

#include <iostream>
#include "vector_node.h"



vector_node::vector_node(int node_id, list<int> instances)
{
    this->node_id = node_id;
    while(!instances.empty())
    {
        this->coordinates.push_back(instances.front());
    }
}

int vector_node::get_node_id()
{
    return this->node_id;
}

list<int> vector_node::get_coordinates()
{
    return this->coordinates;
}

void vector_node::add_neighbor(neighbor n)
{
    this->neighbors.push_back(n);
}

void vector_node::delete_neighbor(neighbor n)
{
    for(int i = 0; i < this->neighbors.size(); i++)
    {
        if(this->neighbors[i].get_node_id() == n.get_node_id())
        {
                neighbors.erase(neighbors.begin() + i);
        }
    }
    return;
}









