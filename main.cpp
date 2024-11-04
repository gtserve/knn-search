#include <iostream>
#include <cmath>

#include <input.h>
#include <graph.h>
#include <vamana.h>

#define DATA_PATH "/home/gtserve/Code/k23a-project/data/siftsmall"

using namespace std;

int main() {
    string data_path = DATA_PATH;

    vector<vector<float>> base_vectors;
    readVectors<float> (data_path + "/siftsmall_base.fvecs", base_vectors);

    vector<vector<float>> query_vectors;
    readVectors<float> (data_path + "/siftsmall_query.fvecs", query_vectors);

    vector<vector<int>> gt_vectors;
    readVectors<int> (data_path + "/siftsmall_groundtruth.ivecs", gt_vectors);

    graph<float> G(base_vectors);
    // int R = ceil(log(base_vectors.size()));

    vamana(&G, base_vectors, 2.0, 40, 80);
    // G.print_graph();

    pair<set<int>, set<int>> greedy_result;
    greedy_result = greedy_graph_search(&G, 0, 0, query_vectors[0], 20, 40, false);
    set<int> L = greedy_result.first;
    set<int> V = greedy_result.second;

    set<int> T;
    for (const int &i: gt_vectors[0]) T.insert(i);

    cout << "L[" << L.size() << "]: ";
    for (const int &id: L) cout << id << " ";
    cout << endl;

    cout << "T[" << T.size() << "]: ";
    for (const int &id: T) cout << id << " ";
    cout << endl;

    cout << "Recall: " << recall(L, T) << endl;

    // auto it = L.begin();
    // for (int i = 0; i < L.size(); i++) {
    //     it = next(L.begin(), i);
    //     cout << *it << " " << gt_vectors[0][i] << endl;
    // }
}
