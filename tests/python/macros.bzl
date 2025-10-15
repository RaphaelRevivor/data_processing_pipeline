load("@rules_python//python:defs.bzl", "py_test")

default_args = [
        "--capture=no",
        "--disable-warnings",
        "-v", 
        "--tb=short",
        "--color=yes",
        "-rfEP",
    ] 


def pytest_test(name, srcs, deps = [], args=[], data = [], **kwargs):

    """
    CALL PYTEST
    """

    native.py_test(
        name = name,

        srcs = srcs + [
            "//tests/python/pytest:pytest_wrapper"
        ],

        main = "//tests/python/pytest:pytest_wrapper.py",

        #Some default flags set
        args = default_args + args,

        deps = deps,

        data = data,
        **kwargs,

    )