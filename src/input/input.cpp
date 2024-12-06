/*
* input.cpp
* --------------------------------------------------------------------------------
* Template function to read vectors from .fvecs, ivecs binary files.
* --------------------------------------------------------------------------------
* The vectors are stored in raw little endian. Each vector takes 4+d*4 bytes for
* .fvecs and .ivecs formats, where d is the dimensionality of the vector.
* --------------------------------------------------------------------------------
*/

#include "input.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>

#include <utility_functions.h>

using namespace std;


void readSigmodVectors(
    const string &file_path,
    const int vec_dimension,
    const bool queries,
    vector<std::vector<float> > &vectors,
    vector<vector<float> > &filters
) {
    std::cout << "Reading Data from: " << file_path << std::endl;
    std::ifstream ifs(file_path, std::ios::binary);

    if (!ifs.is_open()) {
        std::cerr << "[ERROR]: Opening file: '" << file_path << "'" << std::endl;
        return;
    }

    // Read number of data points / vectors.
    uint32_t N;
    ifs.read(reinterpret_cast<char *>(&N), sizeof(uint32_t));
    std::cout << "Reading " << N << " vectors ... " << std::endl;

    for (int i = 0; i < N; i++) {
        if (queries) {
            float query_type;
            ifs.read(reinterpret_cast<char *>(&query_type), sizeof(float));

            if (query_type == 2 || query_type == 3) {
                ifs.seekg(sizeof(float) * (vec_dimension + 3), ifs.cur);
                continue;
            }

            if (query_type == 0) {
                ifs.seekg(sizeof(float) * 3, ifs.cur);
                vector<float> fs = {-1};
                filters.push_back(fs);
            }

            if (query_type == 1) {
                float temp;
                ifs.read(reinterpret_cast<char *>(&temp), sizeof(float));
                vector<float> fs = {temp};
                filters.push_back(fs);
                ifs.seekg(sizeof(float) * 2, ifs.cur);
            }
        } else {
            // Read filter.
            float temp;
            ifs.read(reinterpret_cast<char *>(&temp), sizeof(float));
            vector<float> fs = {temp};
            filters.push_back(fs);
            // Ignore timestamp.
            ifs.seekg(sizeof(float), ifs.cur);
        }

        // Read vector.
        vector<float> temp(vec_dimension);
        ifs.read(reinterpret_cast<char *>(temp.data()), vec_dimension * sizeof(float));
        vectors.push_back(temp);
    }

    ifs.close();
    std::cout << "Done!" << std::endl;
}

void generateSigmodGroundTruthFile(
    const string &data_file,
    const string &queries_file,
    const string &out_file,
    const int K_max
) {
    vector<vector<float> > data_vectors;
    vector<vector<float> > data_filters;
    readSigmodVectors(
        data_file,
        100,
        false,
        data_vectors,
        data_filters
    );

    vector<vector<float> > query_vectors;
    vector<vector<float> > query_filters;
    readSigmodVectors(
        queries_file,
        100,
        true,
        query_vectors,
        query_filters
    );

    unordered_map<float, unordered_set<int> > nodes_with_filter;
    for (int i = 0; i < data_vectors.size(); i++) {
        for (int j = 0; j < data_filters[i].size(); j++) {
            nodes_with_filter[data_filters[i][j]].insert(i);
        }
    }

    ofstream ofs(out_file, ios::binary);

    if (!ofs.is_open()) {
        std::cerr << "[ERROR]: Opening file: '" << out_file << "'" << std::endl;
        return;
    }

    // Save number of queries.
    int num_queries = query_vectors.size();
    ofs.write(reinterpret_cast<char *>(&num_queries), sizeof(int));

    for (int i = 0; i < query_vectors.size(); ++i) {
        vector<pair<long double, int> > distances;
        unordered_set<int> matching_vectors;

        if (query_filters[i][0] == -1) {
            // Unfiltered search.
            for (int i = 0; i < data_vectors.size(); i++)
                matching_vectors.insert(i);
        } else {
            // Filtered search.
            matching_vectors = nodes_with_filter[query_filters[i][0]];
        }

        for (const auto &node_id: matching_vectors) {
            long double distance = squared_euclidean_distance(data_vectors[node_id], query_vectors[i]);
            distances.push_back({distance, node_id});
        }

        int num_neighbours = distances.size();
        int k_nearest = min(num_neighbours, K_max);

        nth_element(distances.begin(), distances.begin() + k_nearest, distances.end());

        // Save number of k-nearest neighbors.
        ofs.write(reinterpret_cast<char *>(&k_nearest), sizeof(int));

        for (int j = 0; j < k_nearest; ++j)
            ofs.write(reinterpret_cast<char *>(&distances[j].second), sizeof(int));
    }

    ofs.close();
}

void readSigmodGroundTruth(const string &file_name, vector<vector<int> > &ground_truth) {
    std::ifstream ifs(file_name, std::ios::binary);

    if (!ifs.is_open()) {
        std::cerr << "[ERROR]: Opening file: '" << file_name << "'" << std::endl;
        return;
    }

    // Save number of queries.
    int num_queries;
    ifs.read(reinterpret_cast<char *>(&num_queries), sizeof(int));

    ground_truth.resize(num_queries);

    for (int i = 0; i < num_queries; i++) {
        // Read number of k-nearest neighbors.
        int K;
        ifs.read(reinterpret_cast<char *>(&K), sizeof(int));
        ground_truth[i].resize(K);
        ifs.read(reinterpret_cast<char *>(ground_truth[i].data()), K * sizeof(int));
    }

    ifs.close();
}
