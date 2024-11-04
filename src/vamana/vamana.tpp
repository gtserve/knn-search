#ifndef VAMANA_TPP
#define VAMANA_TPP

#include <set>
#include <algorithm>

#include <graph.h>
#include <utility_functions.h>
#include <data_vector.h>

template<typename T>
pair<set<int>, set<int> > greedy_graph_search(graph<T> *graph, const int starting,
                                              const int query,
                                              const int K, const int L) {
    vector_node<T> *starting_node = graph->get_node(starting);
    vector_node<T> *query_node = graph->get_node(query);

    //set that holds node ids and distances that have been visited during the search
    //create set
    //vector<int> visited_nodes;
    set<pair<int, double>, compare_by_second_value> visited_nodes;
    set<int> visited_ids;

    //create a set of pairs(node id,euclidean distance) that hold nodes found in search
    //create set
    //vector<map<int,int>> neighbors;
    set<pair<int, double>, compare_by_second_value> neighbors;
    set<int> neighbors_ids;

    pair<int, double> temp_pair;
    temp_pair.first = starting_node->get_node_id();
    // temp_pair.second = euclidean_distance(starting->get_coordinates(), query->get_coordinates());
    temp_pair.second = starting_node->getDistance(query_node);;

    //temp_map[starting->get_node_id()] = euclidean_distance(starting->get_coordinates(),querry->get_coordinates());
    //neighbors.insert({starting->get_node_id(),euclidean_distance(starting->get_coordinates(),querry->get_coordinates())});
    neighbors.insert(temp_pair);
    //sort(neighbors.begin(),neighbors.end(),compare_by_second_value);

    set<pair<int, double>, compare_by_second_value> difference;
    set_difference(
        neighbors.begin(), neighbors.end(),
        visited_nodes.begin(), visited_nodes.end(),
        inserter(difference, difference.begin())
    );

    while (!difference.empty()) {
        auto iter = difference.begin();
        //add current node exploring(shortest distance to querry) to visited
        visited_nodes.insert({make_pair(iter->first, iter->second)});

        //explore current node in top of the map (shortest distance to querry)
        int cur_node_id = iter->first;
        vector_node<T> *cur_node = graph->get_node(cur_node_id);

        //BUILD GET NEIGHBORS FUNCTION!!!!!
        // vector<vector_node *> list_of_neighbors = cur_node->get_neighbors_list();

        //BUILD NEIGHBOR SIZE FUNCTION!!!!!!!
        //iterate through current exploring node's neighbors and add to list
        for (const auto &neighbour_id: graph->getNodeNeighbours(cur_node_id)) {
            pair<int, double> new_pair;

            //BUILD GET COORDINATES FUNCTION
            new_pair.first = neighbour_id;
            if (query == neighbour_id) continue;
            vector_node<T> *neighbor_node = graph->get_node(neighbour_id);
            // new_pair.second = euclidean_distance(list_of_neighbors[0]->get_coordinates(), query->get_coordinates());
            //new_map[list_of_neighbors[0].get_node_id()] = euclidean_distance(list_of_neighbors[0].get_coordinates(),querry->get_coordinates());
            new_pair.second = neighbor_node->getDistance(query_node);

            //insert node to set of neighbors
            neighbors.insert(new_pair);

            //if search list size exceeds L contain it to L nodes
            if (neighbors.size() > L) {
                auto first = next(neighbors.begin(), L);
                auto last = neighbors.end();
                neighbors.erase(first, last);
            }
        }

        difference.clear();
        set_difference(
            neighbors.begin(), neighbors.end(),
            visited_nodes.begin(), visited_nodes.end(),
            inserter(difference, difference.begin())
        );
    }

    //return set of k nodes closest to querry
    auto first = next(neighbors.begin(), K);
    auto last = neighbors.end();
    neighbors.erase(first, last);

    for (const auto pair: neighbors) neighbors_ids.insert(pair.first);
    for (const auto pair: visited_nodes) visited_ids.insert(pair.first);

    return {neighbors_ids, visited_ids};
}

template<typename T>
void robustPrune(graph<T> *G, int p, set<int> V, const float a, const int R) {
    vector_node<T> *Np = G->get_node(p);

    for (const int n: G->getNodeNeighbours(p)) V.insert(n);
    V.erase(p);
    G->getNodeNeighbours(p).clear();

    while (!V.empty()) {
        int c_best;
        double min_distance = 1e10;
        for (const int c: V) {
            vector_node<T> *Nc = G->get_node(c);
            double candidate_distance = Np->getDistance(Nc);
            if (candidate_distance < min_distance) {
                min_distance = candidate_distance;
                c_best = c;
            }
        }

        vector_node<T> *Nc_best = G->get_node(c_best);
        G->getNodeNeighbours(p).insert(c_best);

        if (G->getNodeNeighbours(p).size() == R) break;

        for (const int c: V) {
            vector_node<T> *Nc = G->get_node(c);
            if (a * Nc_best->getDistance(Nc) <= Np->getDistance(Nc)) V.erase(c);
        }
    }
}

template<typename T>
void vamana(graph<T> *G, vector<DataVector<T> *> vectors, const float a, const int L_max, const int R) {
    G->generate_random_graph(R);

    vector<vector<T> > dataset;
    for (const auto v: vectors) {
        dataset.push_back(v->getComponents());
    }
    int s = medoid(dataset);

    vector<int> rand_sequence = randomPermutation(vectors.size());

    for (const int i: rand_sequence) {
        pair<set<int>, set<int> > temp_pair = greedy_graph_search(G, s, i, 1, L_max);
        set<int> L = temp_pair.first;
        set<int> V = temp_pair.second;

        robustPrune(G, i, V, a, R);

        for (const auto j: G->getNodeNeighbours(i)) {
            if (G->getNodeNeighbours(j).size() + 1 > R) {
                set<int> C;
                for (const int n: G->getNodeNeighbours(j)) C.insert(n);
                C.insert(i);
                robustPrune(G, j, C, a, R);
            } else {
                G->getNodeNeighbours(j).insert(i);
            }
        }
    }
}

#endif // VAMANA_TPP
