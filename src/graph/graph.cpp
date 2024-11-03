//
// Created by Nikos Tsolkas on 21/10/2024.
//


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <utility>
#include <set>
#include "graph.h"
#include "vector_node.h"


using namespace std;





//
// void robust_prune(graph *graph,vector_node *node,vector<vector_node*> candidates, int a,int R)
// {
//     //add to list of candidates the neighbors of given node
//     vector<vector_node*> list_of_neighbors = node->get_neighbors_list();
//     while(node->get_neighbors_size()>0)
//     {
//         candidates.push_back(list_of_neighbors[0]);
//
//         //delete each neighbor added to candidate
//         node->delete_neighbor(list_of_neighbors[0]);
//     }
//
//
//     //check each candidate for potential new neighbor
//     while(!candidates.empty())
//     {
//         //find candidate with minimum distance from node
//         int min_distance = euclidean_distance(candidates[0]->get_coordinates(),node->get_coordinates());
//         int candi_pos = 0;
//         for(int i=1;i<candidates.size();i++)
//         {
//             if (euclidean_distance(candidates[i]->get_coordinates(),node->get_coordinates()) <= min_distance)
//             {
//                 min_distance = euclidean_distance(candidates[i]->get_coordinates(),node->get_coordinates());
//                 candi_pos = i;
//             }
//         }
//
//         //add prevailing candidate to node's neighbors
//         node->add_neighbor(candidates[candi_pos]);
//
//         //check if number of neighbors exceeds predefined R value
//         if(node->get_neighbors_size()>R)
//         {
//             break;
//         }
//
//
//
//         candidates.erase(candidates.begin()+candi_pos);
//     }
// }


