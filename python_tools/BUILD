load("//rules:rules.bzl", "pylint_test")

pylint_test(
  name = "python_tools_pylint_test",
  data = [":python_files"],
)

filegroup(
  name = "python_files",
  srcs = glob(["**/*.py"]),
)