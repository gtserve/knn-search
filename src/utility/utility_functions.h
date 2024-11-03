//
// Created by Nikos Tsolkas on 21/10/2024.
//

#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#include <list>

using namespace std;

//when adding to sets sort by the second value of the pair(node_id,euclidean_distance) to be inserted
struct compare_by_second_value
{
    bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) const;
};


// function to calculate euclidean distance between two vertices. Vertices may have many instances
int euclidean_distance(list<int>,list<int>);

#endif //UTILITY_FUNCTIONS_H
