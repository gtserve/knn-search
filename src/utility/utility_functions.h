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
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <omp.h>
#include <random>

using namespace std;

//when adding to sets sort by the second value of the pair(node_id,euclidean_distance) to be inserted
struct compare_by_second_value {
    bool operator()(const pair<int, double> &p1, const pair<int, double> &p2) const;
};

struct PairHash {
    template<class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const {
        return hash<T1>()(p.first) ^ (hash<T2>()(p.second) << 1) * 0x9e3779b9;
    }
};

vector<int> randomPermutation(const int N);

float recall(const std::set<int> &X, const std::set<int> &T);

std::string getCurrentTimestamp();

// function to calculate euclidean distance between two vertices. Vertices may have many instances
template<typename T>
long double euclidean_distance(
    const vector<T> &v1,
    const vector<T> &v2,
    const double min_dist = 0.0
) {
    if (v1.size() != v2.size()) {
        cerr << "[ERROR]: Attempt to calculate distance between vectors of different size." << endl;
        return -0.1;
    }

    long double d = 0;
    for (int i = 0; i < v1.size(); ++i) {
        long double diff = static_cast<long double>(v1[i] - v2[i]);
        d += diff * diff;

        // if (min_dist != 0.0 && d > min_dist)
        //     return d;
    }

    return sqrt(d);
}

template<typename T>
long double squared_euclidean_distance(
    const vector<T> &v1,
    const vector<T> &v2,
    const double min_dist = 0.0
) {
    if (v1.size() != v2.size()) {
        cerr << "[ERROR]: Attempt to calculate distance between vectors of different size." << endl;
        return -0.1;
    }

    long double d = 0.0;

    for (size_t i = 0; i < v1.size(); ++i) {
        long double diff = static_cast<long double>(v1[i] - v2[i]);
        d += diff * diff;

        // if (min_dist != 0.0 && d > min_dist)
        //     return d;
    }

    return d;
}


template<typename T>
int medoid(const vector<vector<T> > &vectors) {
    /* Returns the index of medoid vector.  */

    if (vectors.size() == 0) {
        cerr << "[ERROR]: Attempt to find medoid in empty dataset!" << endl;
        return -1;
    }

    if (vectors.size() == 1) {
        cerr << "[ERROR]: Attempt to find medoid in dataset with 1 vector!" << endl;
        return -1;
    }

    // Random number generator setup
    std::random_device rd;  // Seed generator
    std::mt19937 gen(rd()); // Mersenne Twister PRNG
    std::uniform_int_distribution<> dis(0, vectors.size() - 1); // Uniform distribution for index

    // Generate a random index and get the corresponding value
    int randomIndex = dis(gen);

    // long double min_distance = numeric_limits<double>::max();
    // int medoid_id = 0;
    //
    // for (int i = 0; i < vectors.size(); i++) {
    //     long double distance = 0.0;
    //
    //     for (int j = 0; j < vectors.size(); j++) {
    //         distance += squared_euclidean_distance(vectors[i], vectors[j]);
    //         if (distance > min_distance)
    //             break;
    //     }
    //
    //     if (distance < min_distance) {
    //         min_distance = distance;
    //         medoid_id = i;
    //     }
    // }

    return randomIndex;
}

#endif //UTILITY_FUNCTIONS_H
