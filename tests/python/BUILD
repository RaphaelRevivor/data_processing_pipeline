load("@rules_python//python:defs.bzl", "py_test")
load("//macros:macros.bzl", "pytest_test")

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
    data = [":testdata"],
)

pytest_test(
    name = "test_generator",
    srcs = ["test_generator.py"],
    deps = [
        "//python_tools/report_generator:generator",
        "@pip//pytest",
        "@rules_python//python/runfiles",
        "//tests/python/pytest:pytest_wrapper",
    ],
    imports = ["."],
)

pytest_test(
    name = "test_generator_empty",
    srcs = ["test_generator_empty.py"],
    deps = [
        "//python_tools/report_generator:generator_empty",
        "@pip//pytest",
        "@rules_python//python/runfiles",
        "//tests/python/pytest:pytest_wrapper",
    ],
    imports = ["."],
)

filegroup(
    name = "testdata",
    srcs = glob(["*.csv", "*.json"]),
    visibility = ["//:__subpackages__"],
)

exports_files(glob(allow_empty = True, include = ["*.csv", "*.json"]))