//
// Created by Nikos Tsolkas on 21/10/2024.
//

#include "utility_functions.h"
#include <vector>

using namespace std;

bool compare_by_second_value::operator()(const pair<int, double> &p1, const pair<int, double> &p2) const {
    if (p1.second == p2.second) {
        return p1.first < p2.first;
    }
    return p1.second < p2.second;
}
