# k-NN Search

A C++17 implementation of graph-based approximate *k*-nearest-neighbor search. The project builds and queries persistent indexes using three related algorithms:

- **Vamana** for unfiltered vector search
- **Filtered Vamana** for queries constrained by filter values
- **Stitched Vamana** for constructing a filtered index from per-filter subgraphs

The command-line tools can build an index, save it in a binary format, reload it for querying, and report recall against supplied ground-truth results. The repository also contains reusable graph, vector, input, and algorithm modules with unit tests.

## Requirements

- A C++17-compatible compiler
- CMake 3.28 or newer
- OpenMP
- An internet connection during initial configuration so CMake can fetch GoogleTest

## Build

```bash
git clone https://github.com/gtserve/knn-search.git
cd knn-search
cmake -S . -B build
cmake --build build
```

This creates separate index and query executables for each implementation:

| Algorithm | Build index | Query index |
| --- | --- | --- |
| Vamana | `index_v` | `query_index_v` |
| Filtered Vamana | `index_fv` | `query_index_fv` |
| Stitched Vamana | `index_sv` | `query_index_sv` |

## Data formats

The unfiltered tools read [TexMex](http://corpus-texmex.irisa.fr/) `.fvecs` vector files and `.ivecs` ground-truth files. The filtered tools use the binary data, query, and ground-truth layout handled by the project's SIGMOD input reader. Datasets and generated indexes are not included in the repository.

## Usage

Build a standard Vamana index from a TexMex vector file:

```bash
./build/index_v \
  --data data/siftsmall/siftsmall_base.fvecs \
  --output data/indexes/siftsmall.bin \
  -a 1.2 -L 120 -R 50
```

Query the saved index and calculate recall:

```bash
./build/query_index_v \
  --index data/indexes/siftsmall.bin \
  --queries data/siftsmall/siftsmall_query.fvecs \
  --gtruth data/siftsmall/siftsmall_groundtruth.ivecs \
  -k 100 -L 120
```

Here, `k` is the number of neighbors returned, `L` controls the search-list size, `R` bounds graph degree, and `a` is the RobustPrune parameter. Run an index or query executable with `--help` to see its supported arguments. The repository's `vamana.sh`, `filtered_vamana.sh`, and `stitched_vamana.sh` scripts provide complete index-and-query examples; adjust their executable and dataset paths before running them.

## Tests

After building, run the test suite from the repository root:

```bash
ctest --test-dir build --output-on-failure
```

The tests cover vector input, data-vector operations, utility functions, graph behavior, and Vamana search routines.

## Project structure

```text
src/
├── data_vectors/  Vector data types and distance operations
├── graph/         Graph nodes, edges, filters, and serialization
├── input/         TexMex and filtered binary input readers
├── utility/       Shared helper functions
└── vamana/        Search, pruning, and index-construction algorithms
```

This project was developed for the course *Software Development for Information Systems* (`K23A`) by Georgios Tservenis and Nikolaos Tsolkas.

## License

Licensed under the [MIT License](LICENSE).
