#include <iostream>
#include <cmath>
#include <chrono>
#include <unistd.h>

#include <input.h>
#include <graph.h>
#include <vamana.h>

#define ERR_MSG_ARG "ERROR: Option -%c requires an argument.\n"
#define ERR_MSG_UNKNOWN "ERROR: Unknown option -%c.\n"
#define ERR_MSG_NOT_PRINT "ERROR: Unknown option character '\\x%x'.\n"

#define DATA_PATH "/home/gtserve/Code/k23a-project/data/siftsmall"
#define MEDOID 8736

typedef struct {
    string vectors_path;
    float a = 2.0;
    int k = 10;
    int L = 10;
    int R = 10;
} OptionsType;

using namespace std;

int main(int argc, char *argv[]) {
    auto time_start = std::chrono::high_resolution_clock::now();

    OptionsType opt;
    int option;
    while ((option = getopt(argc, argv, "f:a:k:L:R:")) != EOF) {
        switch (option) {
            case 'f':
                opt.vectors_path = optarg;
                break;
            case 'a':
                opt.a = atof(optarg);
                break;
            case 'k':
                opt.k = atoi(optarg);
                break;
            case 'L':
                opt.L = atoi(optarg);
                break;
            case 'R':
                opt.R = atoi(optarg);
                break;
            case '?':
                if ((optopt == 'c') || (optopt == 'b')) {
                    fprintf(stderr, ERR_MSG_ARG, optopt);
                } else if (isprint(optopt)) {
                    fprintf(stderr, ERR_MSG_UNKNOWN, optopt);
                } else {
                    fprintf(stderr, ERR_MSG_NOT_PRINT, optopt);
                }
                break;
            default:
                return -1;
        }
    }

    auto vectors_start = std::chrono::high_resolution_clock::now();
    vector<vector<float> > data_vectors;
    vector<vector<float> > data_filters;
    readSigmodVectors(
        opt.vectors_path + "/dummy-data.bin",
        2,
        100,
        false,
        data_vectors,
        data_filters
    );

    vector<vector<float> > query_vectors;
    vector<vector<float> > query_filters;
    readSigmodVectors(
        opt.vectors_path + "/dummy-query.bin",
        4,
        100,
        true,
        query_vectors,
        query_filters
    );

    vector<vector<int> > gt_vectors;
    readTexmexVectors<int>(opt.vectors_path + "/siftsmall_groundtruth.ivecs", gt_vectors);
    auto vectors_end = std::chrono::high_resolution_clock::now();
    auto vectors_duration = std::chrono::duration_cast<std::chrono::milliseconds>(vectors_end - vectors_start);
    cout << "Read vectors! [Time: " << vectors_duration.count() << "ms ]" << endl;

    auto medoid_start = std::chrono::high_resolution_clock::now();
    const int medoid_id = medoid(data_vectors);
    auto medoid_end = std::chrono::high_resolution_clock::now();
    auto medoid_duration = std::chrono::duration_cast<std::chrono::seconds>(medoid_end - medoid_start);
    cout << "Calculated Medoid: " << medoid_id << " [Time: " << medoid_duration.count() << "s ]" << endl;

    graph<float> G(data_vectors, opt.R);

    auto vamana_start = std::chrono::high_resolution_clock::now();
    vamana(&G, data_vectors, MEDOID, opt.a, opt.L, opt.R);
    auto vamana_end = std::chrono::high_resolution_clock::now();
    auto vamana_duration = std::chrono::duration_cast<std::chrono::seconds>(vamana_end - vamana_start);
    cout << "Run Vamana! [Time: " << vamana_duration.count() << "s ]" << endl;

    auto greedy_start = std::chrono::high_resolution_clock::now();
    pair<unordered_set<int>, unordered_set<int> > greedy_result;
    greedy_result = greedy_graph_search(&G, MEDOID, 0, query_vectors[0], opt.k, opt.L, false);
    auto greedy_end = std::chrono::high_resolution_clock::now();
    auto greedy_duration = std::chrono::duration_cast<std::chrono::milliseconds>(greedy_end - greedy_start);
    cout << "Run Greedy! [Time: " << greedy_duration.count() << "ms ]" << endl;

    unordered_set<int> L = greedy_result.first;
    unordered_set<int> V = greedy_result.second;

    unordered_set<int> T;
    for (const int &i: gt_vectors[0]) T.insert(i);

    cout << "k-nearest neighbours [" << L.size() << "]: ";
    for (const int &id: L) cout << id << " ";
    cout << endl;

    cout << "V[" << V.size() << "]: ";
    for (const int &id: V) cout << id << " ";
    cout << endl;

    cout << "T[" << T.size() << "]: ";
    for (const int &id: T) cout << id << " ";
    cout << endl;

    float r = recall(L, T);
    cout << "Recall: " << r << endl;

    auto time_end = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::minutes>(time_end - time_start);
    cout << "[Total Time: " << duration.count() << "m ]" << endl;

    return 0;
}
