//
// Created by Nikos Tsolkas on 21/10/2024.
//

#include <iostream>
#include "neighbor.h"
#include "../utility/utility_functions.h"

neighbor::neighbor(int node_id, list<int> parent_instances, list<int> instances)
{
    this->node_id = node_id;
    this->euclidean_distance=::euclidean_distance(parent_instances, instances);
}

int neighbor::get_distance()
{
    return this->euclidean_distance;
}

int neighbor::get_node_id()
{
    return this->node_id;
}


