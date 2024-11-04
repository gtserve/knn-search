#ifndef VAMANA_TPP
#define VAMANA_TPP

#include <set>
#include <algorithm>

#include <graph.h>
#include <utility_functions.h>
#include <data_vector.h>

template<typename T>
pair<set<int>, set<int> > greedy_graph_search(
        graph<T> *graph,
        const int starting,
        const int query_id,
        vector<T> query_vector,
        const int K,
        const int L,
        const bool vamana) {
    vector_node<T> *starting_node = graph->get_node(starting);
    // vector_node<T> *query_node = graph->get_node(query);

    //set that holds node ids and distances that have been visited during the search

    //create set
    //vector<int> visited_nodes;
    // set<pair<int, double>, compare_by_second_value> visited_nodes;
    set<int> visited_ids;

    //create a set of pairs(node id,euclidean distance) that hold nodes found in search
    //create set
    //vector<map<int,int>> neighbors;
    // set<pair<int, double>, compare_by_second_value> neighbors;
    set<int> neighbors_ids;

    // pair<int, double> temp_pair;
    // temp_pair.first = starting_node->get_node_id();
    // // temp_pair.second = euclidean_distance(starting->get_coordinates(), query->get_coordinates());
    // temp_pair.second = starting_node->getDistance(query_vector);;

    //temp_map[starting->get_node_id()] = euclidean_distance(starting->get_coordinates(),querry->get_coordinates());
    //neighbors.insert({starting->get_node_id(),euclidean_distance(starting->get_coordinates(),querry->get_coordinates())});
    // neighbors.insert(temp_pair);
    //sort(neighbors.begin(),neighbors.end(),compare_by_second_value);

    // set<pair<int, double>, compare_by_second_value> difference;
    // set_difference(
    //     neighbors.begin(), neighbors.end(),
    //     visited_nodes.begin(), visited_nodes.end(),
    //     inserter(difference, difference.begin())
    // );

    neighbors_ids.insert(starting);

    set<int> diff;
    set_difference(
        neighbors_ids.begin(), neighbors_ids.end(),
        visited_ids.begin(), visited_ids.end(),
        inserter(diff, diff.begin())
    );

    while (!diff.empty()) {
        // auto iter = difference.begin();
        //add current node exploring(shortest distance to querry) to visited
        int cur_node_id;
        double min_distance = 1e10;
        for (const int p: diff) {
            vector_node<T> *node_p = graph->get_node(p);
            double cur_distance = node_p->getDistance(query_vector);
            if (cur_distance < min_distance) {
                min_distance = cur_distance;
                cur_node_id = p;
            }
        }

        //explore current node in top of the map (shortest distance to querry)
        // int cur_node_id = iter->first;
        vector_node<T> *cur_node = graph->get_node(cur_node_id);


        //BUILD GET NEIGHBORS FUNCTION!!!!!
        // vector<vector_node *> list_of_neighbors = cur_node->get_neighbors_list();

        for (const int id: graph->getNodeNeighbours(cur_node_id)) neighbors_ids.insert(id);
        visited_ids.insert(cur_node_id);

        if (neighbors_ids.size() > L) {
            vector<pair<double, int>> distances;
            for (const int id: neighbors_ids) {
                vector_node<T> *neighbour_node = graph->get_node(id);
                double distance = neighbour_node->getDistance(query_vector);
                distances.push_back({distance, id});
            }
            sort(distances.begin(), distances.end());

            for (int i = distances.size() - 1; i >= L; i--)
                neighbors_ids.erase(distances[i].second);
        }

        // //BUILD NEIGHBOR SIZE FUNCTION!!!!!!!
        // //iterate through current exploring node's neighbors and add to list
        // for (const auto &neighbour_id: graph->getNodeNeighbours(cur_node_id)) {
        //     pair<int, double> new_pair;
        //
        //     //BUILD GET COORDINATES FUNCTION
        //     new_pair.first = neighbour_id;
        //     if (vamana && query_id == neighbour_id) continue;
        //     vector_node<T> *neighbor_node = graph->get_node(neighbour_id);
        //     // new_pair.second = euclidean_distance(list_of_neighbors[0]->get_coordinates(), query->get_coordinates());
        //     //new_map[list_of_neighbors[0].get_node_id()] = euclidean_distance(list_of_neighbors[0].get_coordinates(),querry->get_coordinates());
        //     new_pair.second = neighbor_node->getDistance(query_vector);
        //
        //     //insert node to set of neighbors
        //     neighbors.insert(new_pair);
        //
        //     //if search list size exceeds L contain it to L nodes
        //     if (neighbors.size() > L) {
        //         auto first = next(neighbors.begin(), L);
        //         auto last = neighbors.end();
        //         neighbors.erase(first, last);
        //     }
        // }

        diff.clear();
        set_difference(
            neighbors_ids.begin(), neighbors_ids.end(),
            visited_ids.begin(), visited_ids.end(),
            inserter(diff, diff.begin())
        );
    }

    if (neighbors_ids.size() > K) {
        vector<pair<double, int>> distances;
        for (const int id: neighbors_ids) {
            vector_node<T> *neighbour_node = graph->get_node(id);
            double distance = neighbour_node->getDistance(query_vector);
            distances.push_back({distance, id});
        }
        sort(distances.begin(), distances.end());

        for (int i = distances.size() - 1; i >= K; i--)
            neighbors_ids.erase(distances[i].second);
    }

    // //return set of k nodes closest to querry
    // auto first = next(neighbors.begin(), K);
    // auto last = neighbors.end();
    // neighbors.erase(first, last);

    // for (const auto pair: neighbors) neighbors_ids.insert(pair.first);
    // for (const auto pair: visited_nodes) visited_ids.insert(pair.first);

    return {neighbors_ids, visited_ids};
}


template<typename T>
void robustPrune(graph<T> *G, int p, set<int> V, const float a, const int R) {
    vector_node<T> *Np = G->get_node(p);

    for (const int n: G->getNodeNeighbours(p)) V.insert(n);
    V.erase(p);
    G->clearNeighbours(p);

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
        G->addEdgeDirected(p, c_best);

        if (G->getNodeNeighbours(p).size() == R) break;

        set<int> V_copy = V;
        for (const int c: V_copy) {
            vector_node<T> *Nc = G->get_node(c);
            if (a * Nc_best->getDistance(Nc) <= Np->getDistance(Nc))
                V.erase(c);
        }
    }
}

template<typename T>
void vamana(graph<T> *G, vector<vector<T>> &data_set, const int medoid_id, const float a, const int L_max, const int R) {
    G->generate_random_graph(R);

    vector<int> rand_sequence = randomPermutation(data_set.size());

    for (const int i: rand_sequence) {
        pair<set<int>, set<int> > temp_pair = greedy_graph_search(G, medoid_id, i, data_set[i], 1, L_max, true);
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
                G->addEdgeDirected(j, i);
            }
        }
    }
}

#endif // VAMANA_TPP
