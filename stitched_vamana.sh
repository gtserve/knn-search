#!/usr/bin/env bash

TIMESTAMP=$(date +"%Y-%m-%d-%H-%M-%S")

# Change these variables if necessary.
EXECUTABLES_DIR="./cmake-build-debug"
DATASET_DIR="./data/sigmod"

INDEX_DIR="./data/indexes"
INDEX_FILE="$INDEX_DIR/index_fv_$TIMESTAMP.bin"

mkdir -p $INDEX_DIR

echo "Creating Index..."
/usr/bin/time -v \
  "$EXECUTABLES_DIR/index_sv" \
    --data "$DATASET_DIR/dummy-data.bin" \
    --output "$INDEX_FILE" \
    -a 1.2 \
    -l 120 \
    -r 32 \
    -R 50
echo -e "\n"

echo "Querying Index ..."
/usr/bin/time -v \
  "$EXECUTABLES_DIR/query_index_sv" \
    --index "$INDEX_FILE" \
    --queries "$DATASET_DIR/dummy-queries.bin" \
    --gtruth "$DATASET_DIR/dummy-groundtruth.bin" \
    -k 100 \
    -L 120
echo -e "\n"

rm -f "$INDEX_FILE"
