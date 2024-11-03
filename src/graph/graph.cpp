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

//initialize graph
graph::graph()
{
    vertices=0;
}


void graph::add_node(int id, list<int> coordinates)
{
    //creating a temp node to add to graph
    vector_node temp(id,coordinates);

    this->vertices++;
    this->nodes.push_back(temp);
}


/*void graph::add_neighbor_to_vector(int node, neighbor n)
{
    this->vertices_array[node].add_neighbor(n);
}
 */


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
        //
        //
        //DEFINE WHAT IS THE NODE ID!!!!!
        //
        //
        //
        graph->add_node(1,temp_coordinates);
    }

    srand(time(NULL));
    for(int i=0;i<graph->get_vertices();i++)
    {
        int number_of_neighbors = rand() % NEIGHBOR;
        for(int j=0;j<number_of_neighbors;j++)
        {
            //find random node in graph to be connected to i
            int cur_neighbor = rand() % graph->get_vertices();

            vector_node *parent_node=graph->get_node(i);

            //return node from vector array
            vector_node *neighbor_node=graph->get_node(cur_neighbor);

            //add edge from parent node to neighgbor
            parent_node->add_neighbor(neighbor_node);

            /*
            //create new neighbor for current node i
            neighbor new_neighbor(neighbor_node->get_node_id(),parent_node->get_coordinates(),neighbor_node->get_coordinates());

            //watch for duplicates entries in neighbors!!!
            graph->add_neighbor_to_vector(cur_neighbor,new_neighbor);
             */
        }
    }

    return *graph;
}


set<pair<int,int>,compare_by_second_value> greedy_graph_search(graph *graph, vector_node *starting, vector_node *querry, int K, int L)
{
    //set that holds node ids and distances that have been visited during the search
    //create set
    //vector<int> visited_nodes;
    set<pair<int,int>,compare_by_second_value> visited_nodes;

    //create a set of pairs(node id,euclidean distance) that hold nodes found in search
    //create set
    //vector<map<int,int>> neighbors;
    set<pair<int,int>,compare_by_second_value> neighbors;

    pair<int,int> temp_pair;
    temp_pair.first = starting->get_node_id();
    temp_pair.second = euclidean_distance(starting->get_coordinates(),querry->get_coordinates());
    //temp_map[starting->get_node_id()] = euclidean_distance(starting->get_coordinates(),querry->get_coordinates());
    //neighbors.insert({starting->get_node_id(),euclidean_distance(starting->get_coordinates(),querry->get_coordinates())});
    neighbors.insert(temp_pair);
    //sort(neighbors.begin(),neighbors.end(),compare_by_second_value);

    set<pair<int,int>> difference;
    set_difference(visited_nodes.begin(),visited_nodes.end(),neighbors.begin(),neighbors.end(),inserter(difference,difference.begin()));

    while(!difference.empty())
    {
        auto iter=neighbors.begin();
        //add current node exploring(shortest distance to querry) to visited
        visited_nodes.insert({make_pair(iter->first,iter->second)});

        //explore current node in top of the map (shortest distance to querry)
        int cur_node_id = iter->first;
        vector_node *cur_node = graph->get_node(cur_node_id);

        //BUILD GET NEIGHBORS FUNCTION!!!!!
        vector<vector_node*> list_of_neighbors = cur_node->get_neighbors_list();

        //BUILD NEIGHBOR SIZE FUNCTION!!!!!!!
        //iterate through current exploring node's neighbors and add to list
        for(int i=0;i<cur_node->get_neighbors_size();i++)
        {
            pair<int,int> new_pair;

            //BUILD GET COORDINATES FUNCTION
            new_pair.first = list_of_neighbors[0]->get_node_id();
            new_pair.second = euclidean_distance(list_of_neighbors[0]->get_coordinates(),querry->get_coordinates());
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

void robust_prune(graph *graph,vector_node *node,vector<vector_node*> candidates, int a,int R)
{
    //add to list of candidates the neighbors of given node
    vector<vector_node*> list_of_neighbors = node->get_neighbors_list();
    while(node->get_neighbors_size()>0)
    {
        candidates.push_back(list_of_neighbors[0]);

        //delete each neighbor added to candidate
        node->delete_neighbor(list_of_neighbors[0]);
    }


    //check each candidate for potential new neighbor
    while(!candidates.empty())
    {
        //find candidate with minimum distance from node
        int min_distance = euclidean_distance(candidates[0]->get_coordinates(),node->get_coordinates());
        int candi_pos = 0;
        for(int i=1;i<candidates.size();i++)
        {
            if (euclidean_distance(candidates[i]->get_coordinates(),node->get_coordinates()) <= min_distance)
            {
                min_distance = euclidean_distance(candidates[i]->get_coordinates(),node->get_coordinates());
                candi_pos = i;
            }
        }

        //add prevailing candidate to node's neighbors
        node->add_neighbor(candidates[candi_pos]);

        //check if number of neighbors exceeds predefined R value
        if(node->get_neighbors_size()>R)
        {
            break;
        }



        candidates.erase(candidates.begin()+candi_pos);
    }
}

int graph::get_vertices()
{
    return this->vertices;
}

vector_node *graph::get_node(int id)
{
    for(int i=0;i<this->vertices;i++)
    {
        if(this->nodes[i].get_node_id()==id)
        {
            vector_node *temp=&(this->nodes[i]);
            return temp;
        }
    }
    return NULL;
}

void graph::print_graph()
{
    for(int i=0;i<this->vertices;i++)
    {
        //cout << this->vertices_array[i].get_id() << endl ;
    }
}
