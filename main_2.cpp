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
#define QUERY_ID 0

typedef struct {
    string vectors_path;
    float a = 2.0;
    int k = 10;
    int L = 10;
    int R = 10;
    int t = 10;
} OptionsType;

using namespace std;

int main(int argc, char *argv[]) {
    auto time_start = std::chrono::high_resolution_clock::now();

    OptionsType opt;
    int option;
    while ((option = getopt(argc, argv, "f:a:k:L:R:t:")) != EOF) {
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
            case 't':
                opt.t = atoi(optarg);
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
    vector<set<float> > data_filters;
    readSigmodVectors(
        opt.vectors_path + "/dummy-data.bin",
        100,
        false,
        data_vectors,
        data_filters
    );

    vector<vector<float> > query_vectors;
    vector<set<float> > query_filters;
    readSigmodVectors(
        opt.vectors_path + "/dummy-queries.bin",
        100,
        true,
        query_vectors,
        query_filters
    );

    vector<vector<int> > gt_vectors;
    readSigmodGroundTruth(
        opt.vectors_path + "/dummy-groundtruth.bin",
        gt_vectors
    );

    auto vectors_end = std::chrono::high_resolution_clock::now();
    auto vectors_duration = std::chrono::duration_cast<std::chrono::milliseconds>(vectors_end - vectors_start);
    cout << "Read vectors! [Time: " << vectors_duration.count() << "ms ]" << endl;

    graph<float> G(data_vectors, data_filters, opt.R);

    auto vamana_start = std::chrono::high_resolution_clock::now();
    filteredVamana(&G, data_vectors, data_filters, opt.a, opt.L, opt.R, opt.t);
    auto vamana_end = std::chrono::high_resolution_clock::now();
    auto vamana_duration = std::chrono::duration_cast<std::chrono::seconds>(vamana_end - vamana_start);
    cout << "Run Vamana! [Time: " << vamana_duration.count() << "s ]" << endl;

    unordered_map<float, int> st = G.getMedoids();
    float unfiltered_recall = 0.0;
    int unfiltered_counter = 0;
    float filtered_recall = 0.0;
    int filtered_counter = 0;
    float total_recall = 0.0;

    for (int i = 0; i < query_vectors.size(); ++i) {
        set<int> S;

        set<float> Fq;
        if (*query_filters[i].begin() == -1) {
            for (const auto &pair: st) {
                Fq.insert(pair.first);
                S.insert(st[pair.second]);
            }
        } else {
            for (const auto &f: query_filters[i]) {
                Fq.insert(f);
                S.insert(st[f]);
            }
        }

        auto greedy_start = std::chrono::high_resolution_clock::now();

        pair<set<int>, set<int> > greedy_result;
        greedy_result = filtered_greedy_graph_search(
            &G, S, i, query_vectors[i], opt.k, opt.L, Fq, false
        );
        auto greedy_end = std::chrono::high_resolution_clock::now();
        auto greedy_duration = std::chrono::duration_cast<std::chrono::milliseconds>(greedy_end - greedy_start);
        cout << "Run Greedy! [Time: " << greedy_duration.count() << "ms ]  ";

        set<int> L = greedy_result.first;
        set<int> V = greedy_result.second;

        set<int> T;
        for (const int &j: gt_vectors[i])
            T.insert(j);

        // cout << "k-nearest neighbours [" << L.size() << "]: ";
        // for (const int &id: L)
        //     cout << id << " ";
        // cout << endl;
        //
        // cout << "V[" << V.size() << "]: ";
        // for (const int &id: V)
        //     cout << id << " ";
        // cout << endl;
        //
        // cout << "T[" << T.size() << "]: ";
        // for (const int &id: T)
        //     cout << id << " ";
        // cout << endl;

        float r = recall(L, T);
        cout << "Recall: " << r << endl;

        if (*query_filters[i].begin() == -1) {
            unfiltered_recall += r;
            unfiltered_counter++;
        } else {
            filtered_recall += r;
            filtered_counter++;
        }
        total_recall += r;
    }

    float avg_unfiltered_recall = unfiltered_recall / static_cast<float>(unfiltered_counter);
    float avg_filtered_recall = filtered_recall / static_cast<float>(filtered_counter);
    float avg_total_recall = total_recall / static_cast<float>(query_vectors.size());

    cout << "Average Recall (Unfiltered): " << avg_unfiltered_recall << endl;
    cout << "Average Recall (Filtered):   " << avg_filtered_recall << endl;
    cout << "Average Recall (Total):      " << avg_total_recall << endl;

    auto time_end = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::minutes>(time_end - time_start);
    cout << "[Total Time: " << duration.count() << "m ]" << endl;

    return 0;
}
