cc_test(
  name = "json_parser_test",
  srcs = ["test_json_parser.cc"],
  deps = [
    "@googletest//:gtest",
    "@googletest//:gtest_main",
    "//libs/parser:parser",
    "@bazel_tools//tools/cpp/runfiles",
  ],
  data = [
    "example.json",
  ],
)