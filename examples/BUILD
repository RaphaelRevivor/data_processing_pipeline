cc_binary(
  name = "example",
  srcs = [
    "main.cc",
    "main.h",
  ],
  deps = [
    "//libs/parser:parser",
    # it seems this is needed for bazel 8 to use an external data file
    "@bazel_tools//tools/cpp/runfiles",
  ],
  data = [
    "example.csv",
    "example.json",
  ]
)

exports_files([
    "example.csv",
    "example.json",
])