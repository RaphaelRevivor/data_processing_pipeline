py_library(
    name = "cleaner_lib",
    srcs = ["cleaner.py"],
    visibility = ["//:__subpackages__"],
    deps = [
        "@rules_python//python/runfiles",   # add this
        "@pip//numpy", #cleaner.py uses numpy
    ],

    imports = ["."],

    data = ["//tests/python:testdata",],
    )

py_binary(
    name = "cleaner",
    srcs = ["cleaner.py"],
    visibility = ["//:__subpackages__"],
    deps = [
        ":cleaner_lib",
        "@rules_python//python/runfiles",   # add this
        "@pip//numpy", #cleaner.py uses numpy
    ],

    imports = ["."],

    data = ["//tests/python:testdata"],

)