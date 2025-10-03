load("@rules_python//python:defs.bzl", "py_test")
#load("@my_python_deps//:requirements.py", "requirement")

default_args = [
        "--capture=no",
        "--disable-warnings",
        "-v", 
        "--tb=short",
        "-color=yes",
        "-rfEP",
    ] 


def pytest_test(name, srcs, deps = [], extra_args = [], data = [], **kwargs):

    """
    CALL PYTEST
    """

    native.py_test(
        name = name,

        srcs = srcs + [
            "//python_tools/pytest:pytest_wrapper"
        ],

        main = "//python_tools/pytest:pytest_wrapper.py",

        #Some default flags set
        args = default_args + extra_args,

        deps = deps,

        data = data,
        **kwargs,

    )