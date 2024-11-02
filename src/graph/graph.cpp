//
// Created by Nikos Tsolkas on 21/10/2024.
//


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "graph.h"
#include "vector_node.h"

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

            vector_node parent_node=graph->get_vector(i);

            //return node from vector array
            vector_node neighbor_node=graph->get_vector(cur_neighbor);

            //create new neighbor for current node i
            neighbor new_neighbor(neighbor_node.get_node_id(),parent_node.get_coordinates(),neighbor_node.get_coordinates());

            //watch for duplicates entries in neighbors!!!
            graph->add_neighbor_to_vector(cur_neighbor,new_neighbor);

        }
    }

    return *graph;
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
