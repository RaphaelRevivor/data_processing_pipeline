load("@rules_python//python:defs.bzl", "py_test")
load("//:bazel-macro/pytest_test.bzl", "pytest_test")


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

pytest_test(
    name = "test_test_cleaner",
    srcs = ["test_cleaner.py"],
    deps = [
        "//python_tools/data_cleaner:cleaner",
        "@pip//pytest",
        "@rules_python//python/runfiles",
        "//python_tools/pytest:pytest_wrapper",
    ],
    imports = ["."],
)

filegroup(
    name = "testdata",
    srcs = glob(["*.csv", "*.json"]),
    visibility = ["//:__subpackages__"],
)

exports_files(glob(allow_empty = True, include = ["*.csv", "*.json"]))