py_library(
    name = "cleaner",
    srcs = ["cleaner.py"],
    visibility = ["//:__subpackages__"],
    deps = [
        "@rules_python//python/runfiles",   # add this
        "@pip//numpy", #cleaner.py uses numpy
    ],

    imports = ["."],

    data = [
        "//tests/python:example1input.csv",
        "//tests/python:example1input.json",
        "//tests/python:example2input.csv",
        "//tests/python:example2input.json",
        "//tests/python:example3input.csv",
        "//tests/python:example3input.json",

        "//tests/python:example1output.csv",
        "//tests/python:example1output.json",
        "//tests/python:example2output.csv",
        "//tests/python:example2output.json",
        "//tests/python:example3output.csv",
        "//tests/python:example3output.json",
    ],
    )