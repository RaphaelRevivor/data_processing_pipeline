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
)

# usage: bazel build //libs/math:generate_stats_file
gen_stats(
  name = "generate_stats_file_pipeline",
  # take the cc_binary as exec tool
  tool = ":generate_stats",
  data = [
    "//output/test:example1_cleaned.json",
  ],
  visibility = [
    "//:__subpackages__",
  ]
)

gen_stats(
  name = "generate_stats_file",
  # take the cc_binary as exec tool
  tool = ":generate_stats",
  data = [
    "//examples:example.csv",
  ],
  visibility = [
    "//:__subpackages__",
  ]
)

gen_stats(
  name = "generate_stats_file_empty",
  # take the cc_binary as exec tool
  tool = ":generate_stats",
  data = [
    "//examples:empty.json",
  ],
  visibility = [
    "//:__subpackages__",
  ]
)