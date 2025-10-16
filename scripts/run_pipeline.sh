#Order of running pipeline: data_cleaning --> cpp_cli_tool --> report_generator (?)
#Called by running bazel run //scripts:run_pipeline data.csv (arg1)

set -e

INPUT_FILE="$1" #$1 is the first argument, in this scenario the filepath
OUTPUT_DIR="$2"

if [-z $INPUT_FILE]; then
    echo "Usage: bazel run //scripts:run_pipeline <input-file>"
    exit 1
fi

#Run CLI tool (?)

echo "====================RUNNING-PIPELINE-ON-$INPUT_FILE===================="

#bazel run //python_tools/data_cleaner:cleaner $INPUT_FILE
#bazel run //cpp_cli_tool:cli $INPUT_FILE
#RUN REPORT GENERATOR HERE EVENTUALLY

echo "Fetching directories..."

WORKSPACE_DIR="$(bazel info workspace)/"
BIN_DIR="$(bazel info bazel-bin)"


CLI_TARGET="//apps/cpp_cli_tool:cli"
PY_TARGET="//python_tools/data_cleaner:cleaner"

#CLI_BIN="$BIN_DIR/apps/cpp_cli_tool/cli" #Path to the cli tools BUILD file
#PY_BIN="$BIN_DIR/python_tools/data_cleaner/cleaner" 

echo "Fetched directories..."

bazel build $CLI_TARGET $PY_TARGET

echo "Running C++ CLI tool on $INPUT_FILE..."
#Call using bazel instead of direct path to bin
bazel run $CLI_TARGET -- $WORKSPACE_DIR$INPUT_FILE

#"$CLI_BIN" "$INPUT_FILE"

echo "Running Python data cleaner tool on $INPUT_FILE..."
bazel run $PY_TARGET -- $WORKSPACE_DIR$INPUT_FILE  "--output-dir=$OUTPUT_DIR"

echo "Generating report of $INPUT_FILE..."

#Build report generator with output dir of cleaner in build file

#Run report generator with output directory as param

echo "Pipeline finished, check $OUTPUT_DIR for results"

bazel run //python_tools/report_generator:generator $OUTPUT_DIR

echo "====================PIPELINE-SUCCESSFUL===================="


chmod +x scripts/run_pipeline.sh

#TO RUN:

# bash scripts/run_pipeline.sh <inputfile_directory> <output_directory>
# example: bash scripts/run_pipeline.sh data_processing_pipeline/tests/python/example3.csv output/tests