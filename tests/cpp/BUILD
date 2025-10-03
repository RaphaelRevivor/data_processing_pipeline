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

cc_test(
  name = "csv_parser_test",
  srcs = ["test_csv_parser.cc"],
  deps = [
    "@googletest//:gtest",
    "@googletest//:gtest_main",
    "//libs/parser:parser",
    "@bazel_tools//tools/cpp/runfiles",
  ],
  data = [
    "example.csv",
  ],
)

cc_test(
  name = "stats_test",
  srcs = ["test_stats.cc"],
  deps = [
    "@googletest//:gtest",
    "@googletest//:gtest_main",
    "//libs/math:stats",
    "@bazel_tools//tools/cpp/runfiles",
  ],
)