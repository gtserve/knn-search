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

template<typename T>
pair<set<int>, unordered_set<int> > greedy_graph_search(
    graph<T> *graph,
    const int starting,
    const int query_id,
    vector<T> query_vector,
    const int K,
    const int L,
    const bool vamana) {

    unordered_set<int> visited_ids;
    set<int> neighbors_ids;

    neighbors_ids.insert(starting);

    //cout << "here 1" << endl;
    unordered_set<int> diff;
    for(const int p : neighbors_ids)
    {
        if(visited_ids.find(p) == visited_ids.end())
        {
            diff.insert(p);
        }
    }
    /*set_difference(
        neighbors_ids.begin(), neighbors_ids.end(),
        visited_ids.begin(), visited_ids.end(),
        inserter(diff, diff.begin())
    );*/

    //cout << "here 2 " << diff.size() << endl;

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

        //cout << "here 1" << endl;
        diff.clear();
        for(const int p : neighbors_ids)
        {
            if(visited_ids.find(p) == visited_ids.end())
            {
                diff.insert(p);
            }
        }
        /*set_difference(
            neighbors_ids.begin(), neighbors_ids.end(),
            visited_ids.begin(), visited_ids.end(),
            inserter(diff, diff.begin())
        );*/
        //cout << "here 2 " << diff.size() << endl;
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
pair<set<int>, unordered_set<int> > greedy_graph_search_revision(
    graph<T> *graph,
    const int starting,
    const int query_id,
    vector<T> query_vector,
    const int K,
    const int L,
    const bool vamana) {


    //vector that holds distances from nodes to other nodes

    unordered_set<int> visited_ids;
    set<int> neighbors_ids;

    neighbors_ids.insert(starting);

    unordered_set<int> diff;
    for(const int p : neighbors_ids)
    {
        if(visited_ids.find(p) == visited_ids.end())
        {
            diff.insert(p);
        }
    }

    while (!diff.empty()) {
        int cur_node_id;
        double min_distance = 1e10;
        double cur_distance = 0.0;
        long double res = 0.0;
        for (const int p: diff) {
            vector_node<T> *node_p = graph->get_node(p);
            res = graph->getDistance(p,query_id);
            if( res != 0.0  )
            {
                long double cur_distance = res;
            }
            else
            {
                double cur_distance = node_p->getDistance(query_vector);
                graph->addDistance(p,query_id,cur_distance);
            }
            //double cur_distance = node_p->getDistance(query_vector);
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
                double distance = 0.0;
                long double res = graph->getDistance(id,query_id);
                if (res != 0.0  )
                {
                        distance = res;
                }
                else
                {
                    distance = neighbour_node->getDistance(query_vector);
                    graph->addDistance(id,query_id,distance);
                }
                //distance = neighbour_node->getDistance(query_vector);
                distances.push_back({distance, id});
            }
            nth_element(distances.begin(), distances.begin() + L, distances.end());

            for (int i = distances.size() - 1; i >= L; i--)
                neighbors_ids.erase(distances[i].second);
        }


        diff.clear();
        for(const int p : neighbors_ids)
        {
            if(visited_ids.find(p) == visited_ids.end())
            {
                diff.insert(p);
            }
        }
    }

    if (neighbors_ids.size() > K) {
        vector<pair<double, int> > distances;
        for (const int id: neighbors_ids) {
            vector_node<T> *neighbour_node = graph->get_node(id);
            double distance = 0.0;
            long double res = graph->getDistance(id,query_id);
            if (res != 0.0  )
            {
                distance = res;
            }
            else
            {
                distance = neighbour_node->getDistance(query_vector);
                graph->addDistance(id,query_id,distance);
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
void robustPrune(graph<T> *G, const int p, unordered_set<int> &V, const float a, const int R) {
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

        //set<int> V_copy = V;
        for (const int c: V) {
            vector_node<T> *Nc = G->get_node(c);
            if (a * Np_best->getDistance(Nc) <= Np->getDistance(Nc))
                V.erase(c);
        }
    }
}

template<typename T>
void robustPrune_revision(graph<T> *G, const int p, unordered_set<int> &V, const float a, const int R) {
    vector_node<T> *Np = G->get_node(p);

    for (const int n: G->getNodeNeighbours(p)) V.insert(n);
    V.erase(p);
    G->clearNeighbours(p);

    while (!V.empty()) {
        //cout << "TEST TEST 1" << endl;
        int p_best;
        long double min_distance = 1e10;
        for (const int c: V) {
            //cout << "TEST TEST 2" << endl;
            vector_node<T> *Nc = G->get_node(c);
            long double res = G->getDistance(p,c);
            long double candidate_distance = 0.0;
            if (res != 0.0  )
            {
                candidate_distance = res;
            }
            else
            {
                candidate_distance = Np->getDistance(Nc);
                G->addDistance(p,c,candidate_distance);
            }
            if (candidate_distance < min_distance) {
                min_distance = candidate_distance;
                p_best = c;
            }
        }
        //cout << "TEST TEST 3" << endl;
        vector_node<T> *Np_best = G->get_node(p_best);
        G->addEdgeDirected(p, p_best);

        if (G->getNodeNeighbours(p).size() == R) break;

        //set<int> V_copy = V;
        for (const int c: V) {
            //cout << "TEST TEST 4" << endl;
            vector_node<T> *Nc = G->get_node(c);
            long double res_a = G->getDistance(p_best,c);
            long double res_b = G->getDistance(p,c);
            long double dist_a = 0;
            long double dist_b = 0;
            if (res_a != 0.0)
            {
                dist_a = res_a;
            }
            else
            {
                dist_a = Np_best->getDistance(Nc);
                G->addDistance(p_best,c,dist_a);
            }
            //cout << dist_a << endl;
            if (res_b != 0.0)
            {
                dist_b = res_b;
            }
            else
            {
                dist_b = Np->getDistance(Nc);
                G->addDistance(p_best,c,dist_b);
            }
            //cout << dist_b << endl;
            if (a * dist_a <= dist_b) {
                V.erase(c);
                //cout << "TEST TEST 5" << endl;
            }

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

    /*following values only for debugging improved performance*/
    unsigned int use_of_greedy=0;
    unsigned int use_of_robust=0;


    //auto graph_start = std::chrono::high_resolution_clock::now();
    G->generate_random_graph(R);
    /*auto graph_end = std::chrono::high_resolution_clock::now();
    auto graph_duration = std::chrono::duration_cast<std::chrono::milliseconds>(graph_end - graph_start);
    cout << "graph took [Time: " << graph_duration.count() << "ms ]" << endl;
    */

    vector<int> rand_sequence = randomPermutation(data_set.size());

    auto robust_time=0;
    auto greedy_time=0;


    for (const int i: rand_sequence) {
        auto greedy_start = std::chrono::high_resolution_clock::now();
        pair<set<int>, unordered_set<int> > greedy_result = greedy_graph_search_revision(G, medoid_id, i, data_set[i], 1, L_max, true);
        auto greedy_end = std::chrono::high_resolution_clock::now();
        auto greedy_duration = std::chrono::duration_cast<std::chrono::milliseconds>(greedy_end - greedy_start);
        //cout << "revised greedy took [Time: " << greedy_duration.count() << "ms ]" << endl;
        //greedy_time+=greedy_duration.count();

        use_of_greedy++;
        //set<int> L = greedy_result.first;
        unordered_set<int> V = greedy_result.second;

        //auto robust_start = std::chrono::high_resolution_clock::now();
        robustPrune_revision(G, i, V, a, R);
        //auto robust_end = std::chrono::high_resolution_clock::now();
        //auto robust_duration = std::chrono::duration_cast<std::chrono::milliseconds>(robust_end - robust_start);
        //robust_time+=robust_duration.count();

        //cout << "Robust took [Time: " << robust_duration.count() << "ms ]" << endl;
        use_of_robust++;

        for (const int j: G->getNodeNeighbours(i)) {
            if (G->getNodeNeighbours(j).size() + 1 > R) {
                unordered_set<int> C;
                C.reserve(R+1);
                for (const int n: G->getNodeNeighbours(j)) C.insert(n);
                C.insert(i);
                robustPrune_revision(G, j, C, a, R);
                use_of_robust++;
            } else {
                G->addEdgeDirected(j, i);
            }
        }
    }
    printf("use_of_greedy = %i\n", use_of_greedy);
    printf("use_of_robust = %i\n", use_of_robust);
}


#endif // VAMANA_TPP
