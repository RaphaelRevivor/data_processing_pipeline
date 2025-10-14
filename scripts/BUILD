sh_library(
    name = "run_pipeline_lib",
    visibility = ["//visibility:public"],
    #srcs = ["run_pipeline.sh"],
    data = [
        ":run_pipeline", #Sh_binary below
    ],

)

sh_binary(
    name = "run_pipeline",
    srcs = ["run_pipeline.sh",],
    #data = ["//tests/python:testdata",],
    data = [
        "//apps/cpp_cli_tool:cli",
        "//python_tools/data_cleaner:cleaner",
        "//tests/python:testdata",
        ":bash_data"
    ],
    visibility = ["//visibility:__subpackages__"],
    #deps = [":run_pipeline_lib"],
)

filegroup(
    name = "bash_data",
    srcs = glob(["*.csv", "*.json"]),
    visibility = ["//:__subpackages__"],
)