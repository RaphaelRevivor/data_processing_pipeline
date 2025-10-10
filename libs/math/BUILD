load('//libs/math:defs.bzl', 'gen_stats')

cc_library(
  name = "stats",
  srcs = [
    "stats.cc",
  ],
  hdrs = [
    "stats.h",
  ],
    deps = [
    "@nlohmann_json//:json",
  ],
  visibility = [
    "//:__subpackages__",
  ],
)

cc_binary(
    name = "generate_stats",
    srcs = ["generate_stats.cc"],  
    deps = [
        ":stats",
        "//libs/parser:parser_factory",
        "@bazel_tools//tools/cpp/runfiles",
    ],
    data = [
      "example.csv",
    ],
)

# usage: bazel run generate_stats_file -- example.csv
gen_stats(
  name = "generate_stats_file",
  # take the cc_binary as exec tool
  tool = ":generate_stats",
  data = [
    "example.csv",
  ],
)