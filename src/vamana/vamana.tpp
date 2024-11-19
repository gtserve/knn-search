#ifndef VAMANA_TPP
#define VAMANA_TPP

#include <set>
#include <algorithm>

#include <graph.h>
#include <utility_functions.h>


template<typename T>
pair<set<int>, set<int> > greedy_graph_search(
    graph<T> *graph,
    const int starting,
    const int query_id,
    vector<T> query_vector,
    const int K,
    const int L,
    const bool vamana) {
    set<int> visited_ids;
    set<int> neighbors_ids;

    neighbors_ids.insert(starting);

    set<int> diff;
    set_difference(
        neighbors_ids.begin(), neighbors_ids.end(),
        visited_ids.begin(), visited_ids.end(),
        inserter(diff, diff.begin())
    );

    while (!diff.empty()) {
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

        for (const int id: graph->getNodeNeighbours(cur_node_id)) neighbors_ids.insert(id);
        visited_ids.insert(cur_node_id);

        if (neighbors_ids.size() > L) {
            vector<pair<double, int> > distances;
            for (const int id: neighbors_ids) {
                vector_node<T> *neighbour_node = graph->get_node(id);
                double distance = neighbour_node->getDistance(query_vector);
                distances.push_back({distance, id});
            }
            sort(distances.begin(), distances.end());

            for (int i = distances.size() - 1; i >= L; i--)
                neighbors_ids.erase(distances[i].second);
        }

        diff.clear();
        set_difference(
            neighbors_ids.begin(), neighbors_ids.end(),
            visited_ids.begin(), visited_ids.end(),
            inserter(diff, diff.begin())
        );
    }

    if (neighbors_ids.size() > K) {
        vector<pair<double, int> > distances;
        for (const int id: neighbors_ids) {
            vector_node<T> *neighbour_node = graph->get_node(id);
            double distance = neighbour_node->getDistance(query_vector);
            distances.push_back({distance, id});
        }
        sort(distances.begin(), distances.end());

        for (int i = distances.size() - 1; i >= K; i--)
            neighbors_ids.erase(distances[i].second);
    }

    return {neighbors_ids, visited_ids};
}


template<typename T>
void robustPrune(graph<T> *G, const int p, set<int> &V, const float a, const int R) {
    vector_node<T> *Np = G->get_node(p);

    for (const int n: G->getNodeNeighbours(p)) V.insert(n);
    V.erase(p);
    G->clearNeighbours(p);

    while (!V.empty()) {
        int p_best;
        double min_distance = 1e10;
        for (const int c: V) {
            vector_node<T> *Nc = G->get_node(c);
            double candidate_distance = Np->getDistance(Nc);
            if (candidate_distance < min_distance) {
                min_distance = candidate_distance;
                p_best = c;
            }
        }

        vector_node<T> *Np_best = G->get_node(p_best);
        G->addEdgeDirected(p, p_best);

        if (G->getNodeNeighbours(p).size() == R) break;

        set<int> V_copy = V;
        for (const int c: V_copy) {
            vector_node<T> *Nc = G->get_node(c);
            if (a * Np_best->getDistance(Nc) <= Np->getDistance(Nc))
                V.erase(c);
        }
    }
}

template<typename T>
void vamana(
    graph<T> *G,
    vector<vector<T> > &data_set,
    const int medoid_id,
    const float a,
    const int L_max,
    const int R
) {
    G->generate_random_graph(R);

    vector<int> rand_sequence = randomPermutation(data_set.size());

    for (const int i: rand_sequence) {
        pair<set<int>, set<int> > greedy_result = greedy_graph_search(G, medoid_id, i, data_set[i], 1, L_max, true);
        set<int> L = greedy_result.first;
        set<int> V = greedy_result.second;

        robustPrune(G, i, V, a, R);

        for (const int j: G->getNodeNeighbours(i)) {
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
