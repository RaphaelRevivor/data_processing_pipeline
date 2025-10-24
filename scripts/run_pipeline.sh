# TO RUN: ./scripts/run_pipeline.sh tests/python/example1.json output/test

# Order of running pipeline cpp_cli_tool --> data_cleaner --> report_generator 

set -e

INPUT_FILE="$1" 
OUTPUT_DIR="$2"

if [-z $INPUT_FILE]; then
    echo "Usage: bazel run //scripts:run_pipeline <input-file>"
    exit 1
fi

echo "====================RUNNING-PIPELINE-ON-$INPUT_FILE===================="

echo "Fetching directories..."

WORKSPACE_DIR="$(bazel info workspace)/"
BIN_DIR="$(bazel info bazel-bin)"


CLI_TARGET="//apps/cpp_cli_tool:cli"
PY_TARGET="//python_tools/data_cleaner:cleaner"

echo "Fetched directories..."

bazel build $CLI_TARGET $PY_TARGET

echo "Running C++ CLI tool on $INPUT_FILE..."

bazel run $CLI_TARGET -- $WORKSPACE_DIR$INPUT_FILE

echo "Running Python data cleaner tool on $INPUT_FILE..."

bazel run $PY_TARGET -- $WORKSPACE_DIR$INPUT_FILE  "--output-dir=$OUTPUT_DIR"

echo "Generating report of $INPUT_FILE..."

bazel run //python_tools/report_generator:generator_pipeline -- --output_dir $OUTPUT_DIR --input_file output_generate_stats_file_pipeline.json

echo "Pipeline finished, check $(realpath $OUTPUT_DIR) for results"

echo "====================PIPELINE-SUCCESSFUL===================="