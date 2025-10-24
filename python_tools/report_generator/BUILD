py_binary(
  name = "generator",
  srcs = ["generator.py"],
  # set data as custom generation rule as it produces an output file
  data = [
    "@rules_python//python/runfiles",
    "//libs/math:generate_stats_pipeline",
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
