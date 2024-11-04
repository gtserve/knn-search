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
#include <set>

using namespace std;

//when adding to sets sort by the second value of the pair(node_id,euclidean_distance) to be inserted
struct compare_by_second_value
{
    bool operator()(const pair<int, double>& p1, const pair<int, double>& p2) const;
};

vector<int> randomPermutation(const int N);

float recall(const set<int> &X, const set<int> &T);

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

    double min_distance = numeric_limits<double>::max();
    int medoid_id;
    int num_vectors = vectors.size();
    for (int i = 0; i < num_vectors; i++) {
        double distance = 0.0;
        for (int j = 0; j < vectors.size(); j++) {
            // Distance with self is zero.
            distance += euclidean_distance(vectors[i], vectors[j]);
            if (distance > min_distance) break;

        }
        if (distance < min_distance) {
            min_distance = distance;
            medoid_id = i;
        }
    }

    return medoid_id;
}

#endif //UTILITY_FUNCTIONS_H
