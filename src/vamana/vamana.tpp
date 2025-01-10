#ifndef VAMANA_TPP
#define VAMANA_TPP

#include <set>
#include <algorithm>
#include <chrono>

#include <graph.h>
#include <utility_functions.h>

#include <data_vector.h>
#include <queue>
#include <unordered_map>
#include <omp.h>


template<typename T>
pair<set<int>, unordered_set<int> > greedy_graph_search(
    graph<T> *graph,
    const int starting,
    const int query_id,
    vector<T> query_vector,
    const int K,
    const int L,
    const bool vamana
) {
    unordered_set<int> visited_ids;
    set<int> neighbors_ids;

    neighbors_ids.insert(starting);

    set<int> diff;
    for (const int p: neighbors_ids) {
        if (visited_ids.find(p) == visited_ids.end()) {
            diff.insert(p);
        }
    }

    while (!diff.empty()) {
        int cur_node_id;
        double min_distance = 1e10;
        double cur_distance = 0.0;
        for (const int p: diff) {
            vector_node<T> *node_p = graph->get_node(p);
            if (vamana == true) {
                cur_distance = graph->getDistance(p, query_id);
            } else {
                cur_distance = node_p->getDistance(query_vector);
            }
            if (cur_distance < min_distance) {
                min_distance = cur_distance;
                cur_node_id = p;
            }
        }

        for (const int id: graph->getNodeNeighbours(cur_node_id))
            neighbors_ids.insert(id);
        visited_ids.insert(cur_node_id);

        if (neighbors_ids.size() > L) {
            vector<pair<double, int> > distances;
            for (const int id: neighbors_ids) {
                vector_node<T> *neighbour_node = graph->get_node(id);
                double distance = 0.0;
                if (vamana == true) {
                    distance = graph->getDistance(id, query_id);
                } else {
                    distance = neighbour_node->getDistance(query_vector);
                }
                distances.push_back({distance, id});
            }
            nth_element(distances.begin(), distances.begin() + L, distances.end());

            for (int i = distances.size() - 1; i >= L; i--)
                neighbors_ids.erase(distances[i].second);
        }


        diff.clear();
        for (const int p: neighbors_ids) {
            if (visited_ids.find(p) == visited_ids.end()) {
                diff.insert(p);
            }
        }
    }

    if (neighbors_ids.size() > K) {
        vector<pair<double, int> > distances;
        for (const int id: neighbors_ids) {
            vector_node<T> *neighbour_node = graph->get_node(id);
            double distance = 0.0;
            if (vamana == true) {
                distance = graph->getDistance(id, query_id);
            } else {
                distance = neighbour_node->getDistance(query_vector);
            }
            distances.push_back({distance, id});
        }
        nth_element(distances.begin(), distances.begin() + K, distances.end());

        for (int i = distances.size() - 1; i >= K; i--)
            neighbors_ids.erase(distances[i].second);
    }

    return {neighbors_ids, visited_ids};
}

template<typename T>
pair<set<int>, unordered_set<int> > filtered_greedy_graph_search(
    graph<T> *graph,
    set<int> starting_nodes,
    const int query_id,
    vector<T> query_vector,
    const int K,
    const int L,
    set<float> Fq,
    const bool vamana
) {
    unordered_set<int> visited_ids;
    set<int> neighbors_ids;

    // if (*Fq.begin() == -1) {
    //     // Unfiltered search.
    //     pair<set<int>, set<int> > greedy_result = greedy_graph_search(
    //         graph, *starting_nodes.begin(), query_id, query_vector, K, L, vamana
    //     );
    //     return greedy_result;
    // }

    for (const int i: starting_nodes) {
        vector_node<T> *node = graph->get_node(i);
        set<float> Fs = node->getFilters();

        set<float> F_inter;
        std::set_intersection(
            Fs.begin(), Fs.end(),
            Fq.begin(), Fq.end(),
            std::inserter(F_inter, F_inter.begin())
        );

        if (!F_inter.empty())
            neighbors_ids.insert(i);
    }

    set<int> diff;
    for (const int p: neighbors_ids) {
        if (visited_ids.find(p) == visited_ids.end()) {
            diff.insert(p);
        }
    }

    while (!diff.empty()) {
        int cur_node_id;
        double min_distance = 1e10;
        double cur_distance = 0.0;
        for (const int p: diff) {
            vector_node<T> *node_p = graph->get_node(p);
            if (vamana == true) {
                cur_distance = graph->getDistance(p, query_id);
            } else {
                cur_distance = node_p->getDistance(query_vector);
            }
            if (cur_distance < min_distance) {
                min_distance = cur_distance;
                cur_node_id = p;
            }
        }

        visited_ids.insert(cur_node_id);

        for (const int id: graph->getNodeNeighbours(cur_node_id)) {
            if (visited_ids.find(id) != visited_ids.end())
                continue;

            set<float> Fp = graph->get_node(id)->getFilters();
            set<float> F_inter;
            std::set_intersection(
                Fp.begin(), Fp.end(),
                Fq.begin(), Fq.end(),
                std::inserter(F_inter, F_inter.begin())
            );
            if (!F_inter.empty())
                neighbors_ids.insert(id);
        }

        if (neighbors_ids.size() > L) {
            vector<pair<double, int> > distances;
            for (const int id: neighbors_ids) {
                vector_node<T> *neighbour_node = graph->get_node(id);
                double distance = 0.0;

                if (vamana == true) {
                    distance = graph->getDistance(id, query_id);
                } else {
                    distance = neighbour_node->getDistance(query_vector);
                }
                distances.push_back({distance, id});
            }
            nth_element(distances.begin(), distances.begin() + L, distances.end());

            for (int i = distances.size() - 1; i >= L; i--)
                neighbors_ids.erase(distances[i].second);
        }

        diff.clear();
        for (const int p: neighbors_ids) {
            if (visited_ids.find(p) == visited_ids.end()) {
                diff.insert(p);
            }
        }
    }

    if (neighbors_ids.size() > K) {
        vector<pair<double, int> > distances;
        for (const int id: neighbors_ids) {
            vector_node<T> *neighbour_node = graph->get_node(id);
            double distance = 0.0;
            if (vamana == true) {
                distance = graph->getDistance(id, query_id);
            } else {
                distance = neighbour_node->getDistance(query_vector);
            }
            distances.push_back({distance, id});
        }
        nth_element(distances.begin(), distances.begin() + K, distances.end());

        for (int i = distances.size() - 1; i >= K; i--)
            neighbors_ids.erase(distances[i].second);
    }

    return {neighbors_ids, visited_ids};
}


template<typename T>
void robustPrune(
    graph<T> *G, const int p,
    unordered_set<int> &V,
    const float a,
    const int R
) {
    vector_node<T> *Np = G->get_node(p);

    for (const int n: G->getNodeNeighbours(p))
        V.insert(n);
    V.erase(p);
    G->clearNeighbours(p);

    while (!V.empty()) {
        int p_best;
        long double min_distance = 1e10;
        for (const int c: V) {
            vector_node<T> *Nc = G->get_node(c);
            long double candidate_distance = G->getDistance(c, p);
            if (candidate_distance < min_distance) {
                min_distance = candidate_distance;
                p_best = c;
            }
        }

        vector_node<T> *Np_best = G->get_node(p_best);
        G->addEdgeDirected(p, p_best);

        if (G->getNodeNeighbours(p).size() == R)
            break;

        for (auto c = V.begin(); c != V.end();) {
            if (a * G->getDistance(p_best, *c) <= G->getDistance(p, *c)) {
                c = V.erase(c);
                continue;
            }
            ++c;
        }
    }
}

template<typename T>
void filteredRobustPrune(graph<T> *G, const int p, unordered_set<int> &V, const float a, const int R) {
    vector_node<T> *Np = G->get_node(p);

    for (const int n: G->getNodeNeighbours(p))
        V.insert(n);
    V.erase(p);
    G->clearNeighbours(p);

    while (!V.empty()) {
        int p_best;
        long double min_distance = 1e10;
        for (const int c: V) {
            long double candidate_distance = G->getDistance(p, c);
            if (candidate_distance < min_distance) {
                min_distance = candidate_distance;
                p_best = c;
            }
        }

        vector_node<T> *Np_best = G->get_node(p_best);
        G->addEdgeDirected(p, p_best);

        if (G->getNodeNeighbours(p).size() == R)
            break;

        for (auto c = V.begin(); c != V.end();) {
            vector_node<T> *Nc = G->get_node(*c);
            set<float> Fp = Np->getFilters();
            set<float> Fc = Nc->getFilters();
            set<float> Fp_best = Np_best->getFilters();

            std::set<float> F_inter;
            std::set_intersection(
                Fc.begin(), Fc.end(),
                Fp.begin(), Fp.end(),
                std::inserter(F_inter, F_inter.begin()));

            if (!includes(Fp_best.begin(), Fp_best.end(), F_inter.begin(), F_inter.end())) {
                ++c;
                continue;
            }

            if (a * G->getDistance(p_best, *c) <= G->getDistance(p, *c)) {
                c = V.erase(c);
                continue;
            }

            ++c;
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
        pair<set<int>, unordered_set<int> > greedy_result = greedy_graph_search(
            G, medoid_id, i, data_set[i], 1, L_max, true);

        unordered_set<int> V = greedy_result.second;

        robustPrune(G, i, V, a, R);

        for (const int j: G->getNodeNeighbours(i)) {
            if (G->getNodeNeighbours(j).size() + 1 > R) {
                unordered_set<int> C;
                C.reserve(R + 1);
                for (const int n: G->getNodeNeighbours(j))
                    C.insert(n);
                C.insert(i);
                robustPrune(G, j, C, a, R);
            } else {
                G->addEdgeDirected(j, i);
            }
        }
    }
}

template<typename T>
void filteredVamana(
    graph<T> *G,
    vector<vector<T> > &data_set,
    vector<set<float> > &filters,
    const float a,
    const int L_max,
    const int R,
    const int threshold
) {
    unordered_map<float, int> st = G->findMedoids(threshold);
    vector<int> rand_sequence = randomPermutation(data_set.size());
    for (const int i: rand_sequence) {
        set<int> SF_x;
        for (const auto &f: G->get_node(i)->getFilters())
            SF_x.insert(st[f]);

        pair<set<int>, unordered_set<int> > greedy_result;
        greedy_result = filtered_greedy_graph_search(
            G, SF_x, i, data_set[i], 0, L_max, filters[i], true);

        unordered_set<int> V = greedy_result.second;

        filteredRobustPrune(G, i, V, a, R);

        for (const int j: G->getNodeNeighbours(i)) {
            if (G->getNodeNeighbours(j).size() + 1 > R) {
                unordered_set<int> C;
                C.reserve(R + 1);
                for (const int n: G->getNodeNeighbours(j))
                    C.insert(n);
                C.insert(i);
                filteredRobustPrune(G, j, C, a, R);
            } else {
                G->addEdgeDirected(j, i);
            }
        }
    }
}

template<typename T>
void stitchedVamana(
    graph<T> *G,
    const int a,
    const int L_small,
    const int R_small,
    const int R
) {
    unordered_map<float, vector<int> > id_map;
    set<float> all_filters = G->getAllFilters();
    vector<pair<float, graph<T> *>> graphs;

    vector<float> vec_filters;
    for (const auto f: all_filters)
        vec_filters.push_back(f);

#pragma omp parallel for
    for (int i = 0; i < vec_filters.size(); i++) {

        unordered_set<int> Pf = G->get_nodes_for_filter(vec_filters[i]);

        if (Pf.empty() || Pf.size() == 1)
            continue;

        id_map[vec_filters[i]].reserve(Pf.size());

        for (const auto &id: Pf)
            id_map[vec_filters[i]].push_back(id);

        vector<vector<T> > DS_f;
        DS_f.reserve(Pf.size());
        for (const auto &id: Pf) {
            vector_node<T> *node = G->get_node(id);
            vector<T> components = node->getComponents();
            DS_f.push_back(components);
        }

        graph<T> Gf(DS_f, vec_filters[i], R_small);

        auto medoid_start = std::chrono::high_resolution_clock::now();
        int medoid_id = medoid(DS_f);
        auto medoid_end = std::chrono::high_resolution_clock::now();
        auto medoid_duration = std::chrono::duration_cast<std::chrono::milliseconds>(medoid_end - medoid_start);
        cout << "Calculated Medoid: " << medoid_id << " [Time: " << medoid_duration.count() << "ms ]" << endl;

        G->addMedoid(vec_filters[i], id_map[vec_filters[i]][medoid_id]);

        auto vamana_start = std::chrono::high_resolution_clock::now();
        vamana(&Gf, DS_f, medoid_id, a, L_small, R_small);
        auto vamana_end = std::chrono::high_resolution_clock::now();
        auto vamana_duration = std::chrono::duration_cast<std::chrono::milliseconds>(vamana_end - vamana_start);
        cout << "Run Vamana! [Time: " << vamana_duration.count() << "ms ]" << endl;


        graphs.push_back(make_pair(vec_filters[i], &Gf));

        // for (int j = 0; j < Gf.getNumNodes(); j++) {
        //     unordered_set<int> N_out = Gf.getNodeNeighbours(j);
        //     for (const auto &neighbour_id: N_out)
        //         G->addEdgeDirected(id_map[vec_filters[i]][j], neighbour_id);
        // }

        // Stitch
        for (int i = 0; i < DS_f.size(); i++) {
            unordered_set<int> N_out = Gf.getNodeNeighbours(i);
            for (const auto &neighbour_id: N_out)
                G->addEdgeDirected(id_map[f][i], neighbour_id);
        }
    }

    // // Stitch
    for (const auto &pair: graphs) {
        float filter = pair.first;
        graph <T> *Gf = pair.second;
        for (int j = 0; j < Gf->getNumNodes(); j++) {
            unordered_set<int> N_out = Gf->getNodeNeighbours(j);
            for (const auto &neighbour_id: N_out)
                G->addEdgeDirected(id_map[filter][j], neighbour_id);
        }
    }

    for (int i = 0; i < G->getNumNodes(); i++) {
        unordered_set<int> N_out = G->getNodeNeighbours(i);
        filteredRobustPrune(G, i, N_out, a, R);
    }
}


#endif // VAMANA_TPP
