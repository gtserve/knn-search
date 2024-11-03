//
// Created by Nikos Tsolkas on 21/10/2024.
//

#include "utility_functions.h"
#include <cmath>

bool compare_by_second_value::operator()(const pair<int, int>& p1, const pair<int, int>& p2) const
{
    if (p1.second == p2.second)
    {
         return p1.first < p2.first;
    }
    return p1.second < p2.second;
}


int euclidean_distance(list<int> parent_instances,list<int> new_instances)
{
    double d=0;
    list<int>::iterator it_parent = parent_instances.begin();
    list<int>::iterator it_new = new_instances.begin();
    for(int i=0;i<parent_instances.size();i++)
    {
        advance(it_parent,i);
        advance(it_new,i);
        d+= pow((*it_parent) - (*it_new),2);
    }
    return sqrt(d);
}
