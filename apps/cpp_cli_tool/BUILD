cc_binary(
  name = "cli",
  srcs = ["cli.cc"],
  deps = [
    "//libs/parser:parser_factory",
    "//libs/math:stats",
    "@bazel_tools//tools/cpp/runfiles",
  ],
  visibility  = ["//scripts:__subpackages__"],

  data = ["//tests/python:testdata"],

)

