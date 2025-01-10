/* query_index.cpp
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
    const char *short_options = "hi:s:k:L:";
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

    OptionsType options;
    if (inputHandler(options, argc, argv) == -1)
        return -1;

    // Read Queries.
    cout << "Reading Queries from '" << options.queries_path << "' ...\n";
    auto dq_start = chrono::high_resolution_clock::now();
    vector<vector<float> > query_vectors;
    readTexmexVectors<float>(options.queries_path, query_vectors);
    auto dq_end = chrono::high_resolution_clock::now();
    auto dq_duration = chrono::duration_cast<chrono::milliseconds>(dq_end - dq_start);
    cout << "Done! Read " << query_vectors.size() << " vectors. [Time: " << dq_duration.count() << "ms ]\n";

    // Read GroundTruth.
    cout << "Reading Queries from '" << options.queries_path << "' ...\n";
    auto dgt_start = chrono::high_resolution_clock::now();
    vector<vector<int> > gt_vectors;
    readTexmexVectors<int>(options.gt_path, gt_vectors);
    auto dgt_end = chrono::high_resolution_clock::now();
    auto dgt_duration = chrono::duration_cast<chrono::milliseconds>(dgt_end - dgt_start);
    cout << "Done! Read " << gt_vectors.size() << " vectors. [Time: " << dgt_duration.count() << "ms ]\n";

    graph<float> G(options.index_path);
    int medoid_id = G.getMedoid(-1);

    float total_recall = 0.0;

    for (int i = 0; i < query_vectors.size(); ++i) {
        set<int> S;

        auto greedy_start = std::chrono::high_resolution_clock::now();

        pair<set<int>, unordered_set<int> > greedy_result;
        greedy_result = greedy_graph_search(
            &G, medoid_id, i, query_vectors[i], options.k, options.L, false
        );

        auto greedy_end = std::chrono::high_resolution_clock::now();
        auto greedy_duration = std::chrono::duration_cast<std::chrono::milliseconds>(greedy_end - greedy_start);

        set<int> L = greedy_result.first;
        unordered_set<int> V = greedy_result.second;

        set<int> T;
        for (const int &j: gt_vectors[i])
            T.insert(j);

        float r = recall(L, T);
        total_recall += r;

        cout << "[Query #" << i << "]: " << setw(3) << greedy_duration.count() << "ms, Recall = " << r << endl;
    }

    float avg_total_recall = total_recall / static_cast<float>(query_vectors.size());

    cout << endl << "Average Recall (Total):      " << avg_total_recall << endl;

    auto time_end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::minutes>(time_end - time_start);
    cout << "[Total Time: " << duration.count() << "m ]\n";

    return 0;
}
