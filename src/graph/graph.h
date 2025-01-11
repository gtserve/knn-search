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

    unordered_map<float, int> medoids;

public:
    graph(const vector<vector<T> > &vectors, const int R); //initialise graph

    graph(const vector<vector<T> > &vectors); //initialise graph

    graph(const vector<vector<T> > &vectors, const float filter, const int R);

    graph(const vector<vector<T> > &vectors, const vector<set<float> > &filters, const int R); //initialise graph

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

    std::string saveGraphToDir(const string &dir_path = "", const string &file_path = "");

    void loadGraphFromFile(const string &file_name);

    unordered_set<int> getNodesWithFilter(const float filter);

    unordered_map<float, int> getMedoids() const;

    set<float> getAllFilters() const;

    void addMedoid(const float filter, const int id);

    int getMedoid(const float filter);
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
graph<T>::graph(const vector<vector<T> > &vectors, const float filter, const int R) {
    for (int i = 0; i < vectors.size(); i++) {
        auto *new_node = new vector_node<T>(i, vectors[i]);
        this->nodes.push_back(new_node);
        neighbours[i].reserve(R);
    }

    this->total_filters.insert(filter);
}

template<typename T>
graph<T>::graph(const vector<vector<T> > &vectors, const vector<set<float> > &filters, const int R) {
    for (int i = 0; i < vectors.size(); i++) {
        auto *new_node = new vector_node<T>(i, vectors[i], filters[i]);
        this->nodes.push_back(new_node);
        neighbours[i].reserve(R);

        for (const auto &f: filters[i]) {
            this->nodes_with_filter[f].insert(i);
            this->total_filters.insert(f);
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
    if (this->nodes.size() == 1)
        return;

    srand(time(NULL));
    for (int i = 0; i < this->nodes.size(); i++) {
        int max_neighbours = min(this->getNumNodes() - 1, R);
        while (this->neighbours[i].size() < max_neighbours) {
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
        dist = Na->getDistance(Nb);
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
        std::vector<int> Pf(this->nodes_with_filter[f].begin(), this->nodes_with_filter[f].end());

        if (Pf.size() <= threshold) {
            for (int i = 0; i < Pf.size(); i++)
                Rf.insert(Pf[i]);
        } else {
            while (Rf.size() < threshold) {
                int rand_index = rand() % Pf.size();
                Rf.insert(Pf[rand_index]);
            }
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

    this->medoids = m;
    return m;
}

template<typename T>
std::string graph<T>::saveGraphToDir(const string &dir_path, const string &file_path) {
    string timestamp = getCurrentTimestamp();

    string file_name;
    if (!dir_path.empty()) {
        file_name = dir_path + "/graph_" + timestamp + ".bin";
    } else {
        file_name = file_path;
    }

    if (this->nodes.empty()) {
        std::cerr << "[ERROR]: Attempt to save empty Graph!" << std::endl;
        return "";
    }

    ofstream ofs(file_name, ios::binary);

    if (!ofs.is_open()) {
        std::cerr << "[ERROR]: Opening file: '" << file_name << "'" << std::endl;
        return "";
    }

    // Save number of medoids.
    int num_medoids = this->medoids.size();
    ofs.write(reinterpret_cast<char *>(&num_medoids), sizeof(int));

    // Save medoids.
    for (const auto &pair: this->medoids) {
        float filter = pair.first;
        int medoid_id = pair.second;
        ofs.write(reinterpret_cast<char *>(&filter), sizeof(float));
        ofs.write(reinterpret_cast<char *>(&medoid_id), sizeof(int));
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
    // cout << "Saved Graph to '" << file_name << "'" << endl;
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

    // Read number of medoids.
    int num_medoids = this->medoids.size();
    ifs.read(reinterpret_cast<char *>(&num_medoids), sizeof(int));

    // Read medoids.
    for (int i = 0; i < num_medoids; i++) {
        float filter;
        int medoid_id;
        ifs.read(reinterpret_cast<char *>(&filter), sizeof(float));
        ifs.read(reinterpret_cast<char *>(&medoid_id), sizeof(int));
        this->addMedoid(filter, medoid_id);
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
        vector<float> temp_filters(num_filters);
        ifs.read(reinterpret_cast<char *>(temp_filters.data()), num_filters * sizeof(float));
        set<float> filters(temp_filters.begin(), temp_filters.end());

        // Read vector components.
        vector<float> components(num_components);
        ifs.read(reinterpret_cast<char *>(components.data()), num_components * sizeof(float));

        // Create new node.
        auto *new_node = new vector_node<T>(i, components, filters);
        this->nodes[i] = new_node;
    }

    ifs.close();
    cout << "Loaded Graph from '" << file_name << "'" << endl;
}

template <typename T>
unordered_set<int> graph<T>::getNodesWithFilter(const float filter) {
    return this->nodes_with_filter[filter];
}

template <typename T>
unordered_map<float, int> graph<T>::getMedoids() const {
    return this->medoids;
}

template <typename T>
set<float> graph<T>::getAllFilters() const {
    return this->total_filters;
}

template <typename T>
void graph<T>::addMedoid(const float filter, const int id) {
    this->medoids[filter] = id;
}

template <typename T>
int graph<T>::getMedoid(const float filter) {
    int medoid_id = this->medoids[filter];
    return medoid_id;
}

#endif //GRAPH_VECTOR_H
