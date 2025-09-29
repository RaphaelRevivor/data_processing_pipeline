load("@rules_python//python:defs.bzl", "py_test")

py_test(
    name = "test_cleaner",
    srcs = ["test_cleaner.py"],
    deps = [
        "//python_tools/data_cleaner:cleaner",
        "@pip//pytest",
        "@rules_python//python/runfiles",
    ],
    imports = ["."],
)

exports_files([
    "example1input.csv",
    "example1input.json",
    "example2input.csv",
    "example2input.json",
    "example3input.csv",
    "example3input.json",

    "example1output.csv",
    "example1output.json",
    "example2output.csv",
    "example2output.json",
    "example3output.csv",
    "example3output.json",
])