//
// Created by Nikos Tsolkas on 21/10/2024.
//

#include <iostream>
#include "vector_node.h"
#include <utility>

using namespace std;


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

int vector_node::get_neighbors_size()
{
  return this->neighbors.size();
}

vector<vector_node*> vector_node::get_neighbors_list()
{
    vector<vector_node*> neighbors_list;
    auto it = this->neighbors.begin();
    while(it != this->neighbors.end())
    {
      neighbors_list.push_back(it->first);
      it++;
    }

    return neighbors_list;
}

void vector_node::add_neighbor(vector_node* n)
{
    this->neighbors.insert(make_pair(n,euclidean_distance(this->get_coordinates(),n->get_coordinates())));
}

void vector_node::delete_neighbor(vector_node* n)
{
    /*for(int i = 0; i < this->neighbors.size(); i++)
    {
        if(this->neighbors[i].get_node_id() == n.get_node_id())
        {
                neighbors.erase(neighbors.begin() + i);
        }
    }
    return;
    */
    auto it = this->neighbors.begin();
    while(it != this->neighbors.end())
    {
      if(it->first == n)
      {
        this->neighbors.erase(it);
        return;
      }
      it++;
    }
}









