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
    "//examples:example.csv",
    "//examples:example.json",
    ],
)

genrule(
    name = "generate_stats_file",
    srcs = [":generate_stats"],
    outs = ["stats.json"],
    cmd = "$(location :generate_stats) > $@",
)