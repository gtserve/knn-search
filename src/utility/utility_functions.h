//
// Created by Nikos Tsolkas on 21/10/2024.
//

#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#include <iostream>
#include <list>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

//when adding to sets sort by the second value of the pair(node_id,euclidean_distance) to be inserted
struct compare_by_second_value
{
    bool operator()(const pair<int, double>& p1, const pair<int, double>& p2) const;
};

vector<int> randomPermutation(const int N);

// function to calculate euclidean distance between two vertices. Vertices may have many instances
template<typename T>
double euclidean_distance(const vector<T> parent_instances, const vector<T> new_instances) {
    if (parent_instances.size() != new_instances.size()) {
        cerr << "[ERROR]: Attempt to calculate distance between vectors of different size." << endl;
        return -0.1;
    }

    double d = 0;
    for (int i = 0; i < parent_instances.size(); ++i) {
        d += pow((parent_instances[i]) - (new_instances[i]), 2);
    }

    return sqrt(d);
}

template <typename T>
int medoid(const vector<vector<T>> &vectors) {
    /* Returns the index of medoid vector.  */

    if (vectors.size() == 0) {
        cerr << "[ERROR]: Attempt to find medoid in empty dataset!" << endl;
        return -1;
    }

    // Create vector with pairs <distance, vector_id>.
    vector<pair<double, int>> distances;

    for (int i = 0; i < vectors.size(); i++) {
        double distance = 0.0;
        for (int j = 0; j < vectors.size(); j++) {
            // Distance with self is zero.
            distance += euclidean_distance(vectors[i], vectors[j]);
        }
        distances.push_back({distance, i});
    }

    sort(distances.begin(), distances.end());

    return distances[0].second;
}

#endif //UTILITY_FUNCTIONS_H
