load("@rules_python//python:defs.bzl", "py_test")
load("//tests/python:macros.bzl", "pytest_test")

pytest_test(
    name = "test_cleaner",
    srcs = ["test_cleaner.py"],
    deps = [
        "//python_tools/data_cleaner:cleaner",
        "@pip//pytest",
        "@rules_python//python/runfiles",
        "//tests/python/pytest:pytest_wrapper",
    ],
    imports = ["."],
    data = glob(["*.csv", "*.json"])
)

filegroup(
    name = "testdata",
    srcs = glob(["*.csv", "*.json"]),
    visibility = ["//:__subpackages__"],
)

exports_files(glob(allow_empty = True, include = ["*.csv", "*.json"]))