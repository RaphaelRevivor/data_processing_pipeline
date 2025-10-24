py_binary(
  name = "generator_pipeline",
  main = "generator.py",
  srcs = ["generator.py"],
  # set data as custom generation rule as it produces an output file
  data = [
    "@rules_python//python/runfiles",
    "//libs/math:generate_stats_file_pipeline",
  ],
  visibility = ["//:__subpackages__"],
)

py_binary(
  name = "generator",
  main = "generator.py",
  srcs = ["generator.py"],
  # set data as custom generation rule as it produces an output file
  data = [
    "@rules_python//python/runfiles",
    "//libs/math:generate_stats_file",
  ],
  visibility = ["//:__subpackages__"],
)

py_binary(
  name = "generator_empty",
  main = "generator.py",
  srcs = ["generator.py"],
  # set data as custom generation rule as it produces an output file
  data = [
    "@rules_python//python/runfiles",
    "//libs/math:generate_stats_file_empty",
  ],
  visibility = ["//:__subpackages__"],
)
