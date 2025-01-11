/* query_index_fv.cpp
 * -------------------------------------------------------------------------------------------------
 * Read index from file and perform queries with given data set.
 * -------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <getopt.h>
#include <chrono>

#include <graph.h>
#include <input.h>
#include <iomanip>
#include <vamana.h>

using namespace std;

typedef struct {
    string index_path;
    string queries_path;
    string gt_path;
    int k = 10;
    int L = 10;
} OptionsType;

void usage() {
    std::cout << "Usage: ./query_index [OPTIONS]\n";
    std::cout << "Description:\n";
    std::cout << "  > Read Index from binary file.\n";
    std::cout << "  > Perform queries based on given data set and print recall.\n";
    std::cout << "Options:\n";
    std::cout << "  --help, -h                 Show usage.\n";
    std::cout << "  --index, -i [FILE_PATH]    Specify path to index binary file.\n";
    std::cout << "  --queries, -q [FILE_PATH]  Specify path to queries data set.\n";
    std::cout << "  --gtruth, -g [FILE_PATH]   Specify path to ground truth data set.\n";
    std::cout << "  -k [INTEGER]               Specify parameter 'k' for: GreedySearch.\n";
    std::cout << "  -L [INTEGER]               Specify parameter 'L' for: GreedySearch.\n";
}

int inputHandler(OptionsType &options, int argc, char *argv[]) {
    const char *short_options = "hi:q:g:k:L:";
    const option long_options[] = {
        {"help", no_argument, nullptr, 'h'},
        {"index", required_argument, nullptr, 'i'},
        {"queries", required_argument, nullptr, 'q'},
        {"gtruth", required_argument, nullptr, 'g'},
        {nullptr, 0, nullptr, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, short_options, long_options, nullptr)) != -1) {
        switch (opt) {
            case 'h': // --help or -h
                usage();
                return 0;
            case 'i': // --index or -i
                options.index_path = optarg;
                break;
            case 'q': // --queries or -q
                options.queries_path = optarg;
                break;
            case 'g': // --gtruth or -g
                options.gt_path = optarg;
                break;
            case 'k': // -k
                options.k = atoi(optarg);
                break;
            case 'L': // -L
                options.L = atoi(optarg);
                break;
            case '?': // Unknown
                cerr << "Unknown option! Use --help or -h for usage.\n";
                return -1;
            default:
                break;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    auto time_start = std::chrono::high_resolution_clock::now();

    OptionsType opt;
    if (inputHandler(opt, argc, argv) == -1)
        return -1;

    // Read Queries.
    cout << "Reading Queries from '" << opt.queries_path << "' ...\n";
    auto dq_start = chrono::high_resolution_clock::now();
    vector<vector<float> > query_vectors;
    vector<set<float> > query_filters;
    readSigmodVectors(
        opt.queries_path,
        100,
        true,
        query_vectors,
        query_filters
    );
    auto dq_end = chrono::high_resolution_clock::now();
    auto dq_duration = chrono::duration_cast<chrono::milliseconds>(dq_end - dq_start);
    cout << "Done! Read " << query_vectors.size() << " vectors. [Time: " << dq_duration.count() << "ms ]\n";

    // Read GroundTruth.
    cout << "Reading Queries from '" << opt.queries_path << "' ...\n";
    auto dgt_start = chrono::high_resolution_clock::now();
    vector<vector<int> > gt_vectors;
    readSigmodGroundTruth(
        opt.gt_path,
        gt_vectors
    );
    auto dgt_end = chrono::high_resolution_clock::now();
    auto dgt_duration = chrono::duration_cast<chrono::milliseconds>(dgt_end - dgt_start);
    cout << "Done! Read " << gt_vectors.size() << " vectors. [Time: " << dgt_duration.count() << "ms ]\n";

    // Read Index from file.
    graph<float> G(opt.index_path);

    // Run queries.
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

        pair<set<int>, unordered_set<int> > greedy_result;
        greedy_result = filtered_greedy_graph_search(
            &G, S, i, query_vectors[i], opt.k, opt.L, Fq, false
        );

        set<int> L = greedy_result.first;
        unordered_set<int> V = greedy_result.second;

        set<int> T;
        for (const int &j: gt_vectors[i])
            T.insert(j);

        float r = recall(L, T);
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
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    cout << "[Total Time: " << duration.count() << "ms ]" << endl;

    return 0;
}
