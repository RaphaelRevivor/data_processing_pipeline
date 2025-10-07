cc_binary(
  name = "cli",
  srcs = ["cli.cc"],
  deps = [
    "//libs/parser:parser_factory",
    "//libs/math:stats",
    "@bazel_tools//tools/cpp/runfiles",
  ],

  data = [
    "//tests/python:example1.json",
    ],
)

