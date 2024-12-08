//
// Created by Nikos Tsolkas on 21/10/2024.
//

#include "utility_functions.h"
#include <random>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <chrono>
#include <iomanip>

using namespace std;

bool compare_by_second_value::operator()(const pair<int, double> &p1, const pair<int, double> &p2) const {
    if (p1.second == p2.second) {
        return p1.first < p2.first;
    }
    return p1.second < p2.second;
}

vector<int> randomPermutation(const int N) {
    // Create sequence 0, 1, 2, ... N-1
    vector<int> sequence(N);
    for (int i = 0; i < N; i++) {
        sequence[i] = i;
    }

    // Shuffle sequence.
    srand(time(NULL));
    shuffle(sequence.begin(), sequence.end(), std::mt19937(std::random_device()()));
    return sequence;
}

float recall(const set<int> &X, const set<int> &T) {
    if (X.empty())
        return 0;

    set<int> I;
    set_intersection(
        X.begin(), X.end(),
        T.begin(), T.end(),
        inserter(I, I.begin()));

    return static_cast<float> (I.size()) / static_cast<float> (X.size());
}

std::string getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);

    // Convert to local time
    std::tm local_time;
    localtime_r(&time_t_now, &local_time);

    // Format time into a string
    std::ostringstream timestamp;
    timestamp << std::put_time(&local_time, "%H-%M-%S");
    return timestamp.str();
}
