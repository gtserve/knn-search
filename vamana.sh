#!/usr/bin/env bash

TIMESTAMP=$(date +"%Y-%m-%d-%H-%M-%S")

# Change these variables if necessary.
EXECUTABLES_DIR="./cmake-build-debug"
DATASET_DIR="./data/siftsmall"

INDEX_DIR="./data/indexes"
INDEX_FILE="$INDEX_DIR/index_$TIMESTAMP.bin"

mkdir -p $INDEX_DIR

echo "Creating Index..."
/usr/bin/time -v \
  "$EXECUTABLES_DIR/index_v" \
    --data "$DATASET_DIR/siftsmall_base.fvecs" \
    --output "$INDEX_FILE" \
    -a 1.2 \
    -L 120 \
    -R 50
echo -e "\n"

echo "Querying Index ..."
/usr/bin/time -v \
  "$EXECUTABLES_DIR/query_index_v" \
    --index "$INDEX_FILE" \
    --queries "$DATASET_DIR/siftsmall_query.fvecs" \
    --gtruth "$DATASET_DIR/siftsmall_groundtruth.ivecs" \
    -k 100 \
    -L 120
echo -e "\n"

rm -f "$INDEX_FILE"
