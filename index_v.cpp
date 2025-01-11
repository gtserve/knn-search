/* index_v.cpp
 * -------------------------------------------------------------------------------------------------
 * Create an Index using Vamana and save Index to binary file.
 * -------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <getopt.h>
#include <chrono>

#include <graph.h>
#include <input.h>
#include <vamana.h>

using namespace std;

typedef struct {
    string data_file;
    string output_dir;
    float a = 1.0;
    int L = 10;
    int R = 10;
} OptionsType;

void usage() {
    std::cout << "Usage: ./create_index [OPTIONS]\n";
    std::cout << "Description:\n";
    std::cout << "  > Create an index from specified data set using Vamana.\n";
    std::cout << "  > Save index in binary format to specified file.\n";
    std::cout << "Options:\n";
    std::cout << "  --help, -h                 Show usage.\n";
    std::cout << "  --data, -d [FILE_PATH]     Specify path to data set file.\n";
    std::cout << "  --output, -o [DIR_PATH]    Specify directory path to save index file.\n";
    std::cout << "  -a [FLOAT]                 Specify parameter 'a' for: RobustPrune.\n";
    std::cout << "  -L [INTEGER]               Specify parameter 'L' for: Vamana.\n";
    std::cout << "  -R [INTEGER]               Specify parameter 'R' for: Vamana, RobustPrune.\n";
}

int inputHandler(OptionsType &options, int argc, char *argv[]) {
    const char *short_options = "hd:o:a:L:R:";
    const option long_options[] = {
        {"help", no_argument, nullptr, 'h'},
        {"data", required_argument, nullptr, 'd'},
        {"output", required_argument, nullptr, 'o'},
        {nullptr, 0, nullptr, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, short_options, long_options, nullptr)) != -1) {
        switch (opt) {
            case 'h': // --help or -h
                usage();
                return 0;
            case 'd': // --data or -d
                options.data_file = optarg;
                break;
            case 'o': // --output or -o
                options.output_dir = optarg;
                break;
            case 'a': // -a
                options.a = atof(optarg);
                break;
            case 'L': // -L
                options.L = atoi(optarg);
                break;
            case 'R': // -R
                options.R = atoi(optarg);
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

    cout << "Reading data from '" << options.data_file << "' ...\n";
    auto data_start = chrono::high_resolution_clock::now();
    vector<vector<float> > data;
    readTexmexVectors(options.data_file, data);
    auto data_end = chrono::high_resolution_clock::now();
    auto data_duration = chrono::duration_cast<chrono::milliseconds>(data_end - data_start);
    cout << "Done! Read " << data.size() << " vectors. [Time: " << data_duration.count() << "ms ]\n";

    graph<float> G(data, options.R);

    cout << "Calculating medoid ...\n";
    auto medoid_start = chrono::high_resolution_clock::now();
    const int medoid_id = medoid(data);
    auto medoid_end = chrono::high_resolution_clock::now();
    auto medoid_duration = chrono::duration_cast<chrono::seconds>(medoid_end - medoid_start);
    cout << "Done! Medoid ID: " << medoid_id << " [Time: " << medoid_duration.count() << "s ]\n";

    cout << "Running Vamana ...\n";
    auto vamana_start = chrono::high_resolution_clock::now();
    vamana(&G, data, medoid_id, options.a, options.L, options.R);
    auto vamana_end = chrono::high_resolution_clock::now();
    auto vamana_duration = chrono::duration_cast<chrono::seconds>(vamana_end - vamana_start);
    cout << "Done! [Time: " << vamana_duration.count() << "s ]\n";

    G.addMedoid(-1, medoid_id);

    cout << "Saving index ...\n";
    auto save_start = chrono::high_resolution_clock::now();
    string index_path = G.saveGraphToDir("", options.output_dir);
    auto save_end = chrono::high_resolution_clock::now();
    auto save_duration = chrono::duration_cast<chrono::milliseconds>(save_end - save_start);
    cout << "Done! [Time: " << save_duration.count() << "ms ]\n";

    auto time_end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::minutes>(time_end - time_start);
    cout << "[Total Time: " << duration.count() << "m ]\n";

    return 0;
}
