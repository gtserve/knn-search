//
// Created by Nikos Tsolkas on 21/10/2024.
//

#include "utility_functions.h"
#include <cmath>


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
