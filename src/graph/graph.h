//
// Created by Nikos Tsolkas on 20/10/2024.
//

#ifndef GRAPH_VECTOR_H
#define GRAPH_VECTOR_H

#include <cstdlib>
#include <vector>
#include <set>
#include <cwchar>
#include <fstream>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include <vector_node.h>
#include <data_vector.h>


template<typename T>
class graph {
private:
    vector<vector_node<T> *> nodes; //vector that stores alla vertices

    map<int, unordered_set<int> > neighbours; // Adjacency List

    unordered_map<float, unordered_set<int> > nodes_with_filter;
    //map that stores what nodes are associated with which filter

    //unordered map for storing distances TEST TEST
    unordered_map<pair<int, int>, long double, PairHash> distances_map;

    set<float> total_filters;

public:
    graph(const vector<vector<T> > &vectors, const int R); //initialise graph

    graph(const vector<vector<T> > &vectors); //initialise graph

    graph(const vector<vector<T> > &vectors, const int R, const vector<vector<float> > &filters); //initialise graph

    graph(const string &file_name);

    ~graph();

    void generate_random_graph(const int R);

    void print(const bool vectors = false);

    int getNumNodes(); //return number of vertices in graph

    vector_node<T> *get_node(int);

    unordered_set<int> getNodeNeighbours(int id);

    void addEdgeDirected(int u, int v);

    void deleteEdgeDirected(int u, int v);

    void clearNeighbours(int id);


    //testing new unordered map for storing distances
    long double getDistance(int x, int y);

    void addDistance(int x, int y, long double distance);

    void add_node_filter(int f, int node);

    unordered_set<int> get_nodes_for_filter(int f);

    unordered_map<float, int> findMedoids(const int threshold);

    std::string saveGraphToDir(const string &dir_path);

    void loadGraphFromFile(const string &file_name);
};

//initialize graph
template<typename T>
graph<T>::graph(const vector<vector<T> > &vectors) {
    for (int i = 0; i < vectors.size(); i++) {
        auto *new_node = new vector_node<T>(i, vectors[i]);
        this->nodes.push_back(new_node);
    }
}

template<typename T>
graph<T>::graph(const vector<vector<T> > &vectors, const int R) {
    for (int i = 0; i < vectors.size(); i++) {
        auto *new_node = new vector_node<T>(i, vectors[i]);
        this->nodes.push_back(new_node);
        neighbours[i].reserve(R);
    }
}

template<typename T>
graph<T>::graph(const vector<vector<T> > &vectors, const int R, const vector<vector<float> > &filters) {
    for (int i = 0; i < vectors.size(); i++) {
        auto *new_node = new vector_node<T>(i, vectors[i], filters[i]);
        this->nodes.push_back(new_node);
        neighbours[i].reserve(R);

        for (int j = 0; j < filters[i].size(); j++) {
            this->nodes_with_filter[filters[i][j]].insert(i);
            this->total_filters.insert(filters[i][j]);
        }
    }
}

template <typename T>
graph<T>::graph(const string &file_name) {
    this->loadGraphFromFile(file_name);
}

template<typename T>
graph<T>::~graph() {
    for (int i = 0; i < this->nodes.size(); i++) {
        delete(this->nodes[i]);
    }
}

template<typename T>
void graph<T>::generate_random_graph(const int R) {
    srand(time(NULL));

    for (int i = 0; i < this->nodes.size(); i++) {
        while (this->neighbours[i].size() < 2) {
            //find random node in graph to be connected to i
            int cur_neighbor = rand() % this->nodes.size();
            if (cur_neighbor != i)
                this->neighbours[i].insert(cur_neighbor);
        }
    }
}

template<typename T>
int graph<T>::getNumNodes() {
    return this->nodes.size();
}

template<typename T>
vector_node<T> *graph<T>::get_node(int id) {
    return this->nodes[id];
}

template<typename T>
unordered_set<int> graph<T>::getNodeNeighbours(const int id) {
    return this->neighbours[id];
}

template<typename T>
void graph<T>::print(const bool vectors) {
    cout << "--------------------------------------------------" << endl;
    cout << "  Graph" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Adjacency List:" << endl;
    for (const auto &pair: this->neighbours) {
        cout << "N[" << pair.first << "] -> ";
        for (const auto &neighbour: pair.second) {
            cout << "N[" << neighbour << "], ";
        }
        cout << "\b\b" << endl;
    }
    cout << endl;

    if (vectors) {
        cout << "Node Vectors:" << endl;
        for (int i = 0; i < this->nodes.size(); i++) {
            cout << "N[" << i << "]: (";
            for (const auto &c: this->nodes[i]->getComponents()) {
                cout << c << ", ";
            }
            cout << "\b\b)" << endl;
        }
    }
    cout << endl << endl;
}

template<typename T>
void graph<T>::addEdgeDirected(const int u, const int v) {
    this->neighbours[u].insert(v);
}

template<typename T>
void graph<T>::deleteEdgeDirected(const int u, const int v) {
    this->neighbours[u].erase(v);
}

template<typename T>
void graph<T>::clearNeighbours(const int id) {
    this->neighbours[id].clear();
}

template<typename T>
long double graph<T>::getDistance(int x, int y) {
    if (x == y)
        return 0.0;

    int a = min(x, y);
    int b = max(x, y);

    long double dist = distances_map[{a, b}];
    if (dist == 0.0) {
        vector_node<T> *Na = this->get_node(a);
        vector_node<T> *Nb = this->get_node(b);
        dist = Na.getDistance(Nb);
        distances_map[{a, b}] = dist;
    }
    return dist;
}

template<typename T>
void graph<T>::addDistance(int x, int y, long double distance) {
    this->distances_map[{min(x, y), max(x, y)}] = distance;
}

template<typename T>
void graph<T>::add_node_filter(int f, int node) {
    this->nodes_with_filter[f].insert(node);
}

template<typename T>
unordered_set<int> graph<T>::get_nodes_for_filter(int f) {
    return this->nodes_with_filter[f];
}

template<typename T>
unordered_map<float, int> graph<T>::findMedoids(const int threshold) {
    unordered_map<float, int> m;
    unordered_map<int, int> t;

    for (const auto &f: this->total_filters) {
        srand(time(NULL));
        unordered_set<int> Rf;
        std::vector<int> setVector(this->nodes_with_filter[f].begin(), this->nodes_with_filter[f].end());

        while (Rf.size() < threshold) {
            int rand_index = rand() % this->nodes_with_filter[f].size();
            Rf.insert(setVector[rand_index]);
        }

        int min_count = 1e6;
        int min_node_id = -1;
        for (const auto &node_id: Rf) {
            if (t[node_id] < min_count) {
                min_node_id = node_id;
                min_count = t[node_id];
            }
        }

        m[f] = min_node_id;
        t[min_node_id] += 1;
    }
    return m;
}

template<typename T>
std::string graph<T>::saveGraphToDir(const string &dir_path) {
    string file_name = dir_path + "/graph.bin";

    if (this->nodes.empty()) {
        std::cerr << "[ERROR]: Attempt to save empty Graph!" << std::endl;
        return "";
    }

    ofstream ofs(file_name, ios::binary);

    if (!ofs.is_open()) {
        std::cerr << "[ERROR]: Opening file: '" << file_name << "'" << std::endl;
        return "";
    }

    // Save number of nodes.
    int num_nodes = this->nodes.size();
    ofs.write(reinterpret_cast<char *>(&num_nodes), sizeof(int));

    // Save vector dimension / number of components.
    int num_components = this->nodes[0]->getComponents().size();
    ofs.write(reinterpret_cast<char *>(&num_components), sizeof(int));

    for (int i = 0; i < this->nodes.size(); i++) {
        // Save number of neighbours.
        int num_neighbours = this->neighbours[i].size();
        ofs.write(reinterpret_cast<char *>(&num_neighbours), sizeof(int));

        // Save neighbour ids.
        for (auto n: this->neighbours[i])
            ofs.write(reinterpret_cast<char *>(&n), sizeof(int));

        // Save number of filters.
        int num_filters = this->nodes[i]->getFilters().size();
        ofs.write(reinterpret_cast<char *>(&num_filters), sizeof(int));

        // Save filters.
        for (auto f: this->nodes[i]->getFilters())
            ofs.write(reinterpret_cast<char *>(&f), sizeof(float));

        // Save vector components.
        ofs.write(reinterpret_cast<char *>(this->nodes[i]->getComponents().data()), sizeof(float) * num_components);
    }

    ofs.close();
    return file_name;
}

template <typename T>
void graph<T>::loadGraphFromFile(const string &file_name) {

    if (!this->nodes.empty()) {
        std::cerr << "[ERROR]: Attempt to load file in non-empty Graph!" << std::endl;
        return;
    }

    ifstream ifs(file_name, ios::binary);

    if (!ifs.is_open()) {
        std::cerr << "[ERROR]: Opening file: '" << file_name << "'" << std::endl;
        return;
    }

    // Read number of nodes.
    int num_nodes;
    ifs.read(reinterpret_cast<char *>(&num_nodes), sizeof(int));
    this->nodes.resize(num_nodes);

    // Read vector dimension / number of components.
    int num_components;
    ifs.read(reinterpret_cast<char *>(&num_components), sizeof(int));

    for (int i = 0; i < num_nodes; i++) {
        // Read number of neighbours.
        int num_neighbours;
        ifs.read(reinterpret_cast<char *>(&num_neighbours), sizeof(int));
        this->neighbours[i].reserve(num_neighbours);

        // Read neighbours.
        for (int j = 0; j < num_neighbours; j++) {
            int neighbour_id;
            ifs.read(reinterpret_cast<char *>(&neighbour_id), sizeof(int));
            this->neighbours[i].insert(neighbour_id);
        }

        // Read number of filters.
        int num_filters;
        ifs.read(reinterpret_cast<char *>(&num_filters), sizeof(int));

        // Read filters.
        vector<float> filters(num_filters);
        ifs.read(reinterpret_cast<char *>(filters.data()), num_filters * sizeof(float));

        // Read vector components.
        vector<float> components(num_components);
        ifs.read(reinterpret_cast<char *>(components.data()), num_components * sizeof(float));

        // Create new node.
        auto *new_node = new vector_node<T>(i, components, filters);
        // auto *new_node = new vector_node<T>(i, components);
        this->nodes[i] = new_node;
    }

    ifs.close();
}

#endif //GRAPH_VECTOR_H
