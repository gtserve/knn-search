//
// Created by Nikos Tsolkas on 21/10/2024.
//


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "graph.h"
#include "vector_node.h"
#include "../utility/utility_functions.h"

using namespace std;

//initialize graph
graph::graph()
{
    vertices=0;
}


void graph::add_vector(int id, list<int> coordinates)
{
    //creating a temp node to add to graph
    vector_node temp(id,coordinates);

    this->vertices++;
    this->vertices_array.push_back(temp);
}


void graph::add_neighbor_to_vector(int node, neighbor n)
{
    this->vertices_array[node].add_neighbor(n);
}


graph generate_random_graph(graph *graph, fstream &fp)
{
    string line;
    //get each line from file
    while(getline(fp, line))
    {
        //get each character form each line
        stringstream ss1(line);
        string token;
        int temp_coordinate;
        list<int> temp_coordinates;
        //get each character from line and add it to list of coordinates
        while(ss1 >> token)
        {
            //using atoi cause character is of type char
            temp_coordinate=atoi(token.c_str());
            temp_coordinates.push_back(temp_coordinate);
        }

        //add new vector node to array of vectors
        graph->add_vector(1,temp_coordinates);
    }

    srand(time(NULL));
    for(int i=0;i<graph->get_vertices();i++)
    {
        int number_of_neighbors = rand() % NEIGHBOR;
        for(int j=0;j<number_of_neighbors;j++)
        {
            //find random node in graph to be connected to i
            int cur_neighbor = rand() % graph->get_vertices();

            vector_node *parent_node=graph->get_vector(i);

            //return node from vector array
            vector_node *neighbor_node=graph->get_vector(cur_neighbor);

            //create new neighbor for current node i
            neighbor new_neighbor(neighbor_node->get_node_id(),parent_node->get_coordinates(),neighbor_node->get_coordinates());

            //watch for duplicates entries in neighbors!!!
            graph->add_neighbor_to_vector(cur_neighbor,new_neighbor);

        }
    }

    return *graph;
}


set<pair<int,int>> greedy_graph_search(graph *graph, vector_node *starting, vector_node *querry, int K, int L)
{
    //set that holds node ids and distances that have been visited during the search
    //create set
    //vector<int> visited_nodes;
    set<pair<int,int>> visited_nodes;

    //create a set of pairs(node id,euclidean distance) that hold nodes found in search
    //create set
    //vector<map<int,int>> neighbors;
    set<pair<int,int>> neighbors;

    pair<int,int> temp_pair;
    temp_pair.first = starting->get_node_id();
    temp_pair.second = euclidean_distance(starting->get_coordinates(),querry->get_coordinates());
    //temp_map[starting->get_node_id()] = euclidean_distance(starting->get_coordinates(),querry->get_coordinates());
    neighbors.insert(temp_pair);

    set<pair<int,int>> difference;
    set_difference(visited_nodes.begin(),visited_nodes.end(),neighbors.begin(),neighbors.end(),inserter(difference,difference.begin()));

    while(!difference.empty())
    {
        auto iter=neighbors.begin();
        //add current node exploring(shortest distance to querry) to visited
        visited_nodes.insert(*iter);

        //explore current node in top of the map (shortest distance to querry)
        int cur_node_id = iter->first;
        vector_node *cur_node = graph->get_vector(cur_node_id);

        //BUILD GET NEIGHBORS FUNCTION!!!!!
        neighbor* list_of_neighbors = cur_node->get_neighbors_list();

        //BUILD NEIGHBOR SIZE FUNCTION!!!!!!!
        //iterate through current exploring node's neighbors and add to list
        for(int i=0;i<cur_node.get_neighbors_size();i++)
        {
            pair<int,int> new_pair;

            //BUILD GET COORDINATES FUNCTION
            new_pair.first = list_of_neighbors->get_node_id();
            new_pair.second = euclidean_distance(list_of_neighbors[0].get_coordinates(),querry->get_coordinates());
            //new_map[list_of_neighbors[0].get_node_id()] = euclidean_distance(list_of_neighbors[0].get_coordinates(),querry->get_coordinates());

            //insert node to set of neighbors
            neighbors.insert(new_pair);

            //if search list size exceeds L contain it to L nodes
            if(neighbors.size() > L)
            {
                auto first=next(neighbors.begin(),L);
                auto last=neighbors.end();
                neighbors.erase(first,last);
            }

        }

        set_difference(visited_nodes.begin(),visited_nodes.end(),neighbors.begin(),neighbors.end(),inserter(difference,difference.begin()));
    }

    //return set of k nodes closest to querry
    auto first=next(neighbors.begin(),K);
    auto last=neighbors.end();
    neighbors.erase(first,last);

    return neighbors;
}

int graph::get_vertices()
{
    return this->vertices;
}

void graph::print_graph()
{
    for(int i=0;i<this->vertices;i++)
    {
        //cout << this->vertices_array[i].get_id() << endl ;
    }
}
