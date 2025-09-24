cc_library(
  name = "parser",
  deps = [
    ":json_parser",
    ":parser_factory",
    ":csv_parser",
  ],
  visibility = [
    "//:__subpackages__",
  ],
)

cc_library(
  name = "base_parser",
  srcs = [
    "parser.cc",
  ],
  hdrs = [
    "parser.h",
  ],
)

cc_library(
  name = "json_parser",
  srcs = [
    "json_parser.cc",
  ],
  hdrs = [
    "json_parser.h",
  ],
  deps = [
    ":base_parser",
    "@nlohmann_json//:json",
  ],
)


cc_library(
  name = "csv_parser",
  srcs = [
    "csv_parser.cc",
  ],
  hdrs = [
    "csv_parser.h",
  ],
  deps = [
    ":base_parser",
  ],
)


cc_library(
  name = "parser_factory",
  srcs = [
    "parser_factory.cc",
  ],
  hdrs = [
    "parser_factory.h",
  ],
  deps = [
    ":base_parser",
    ":json_parser",
    ":csv_parser",
  ],
)