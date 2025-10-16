filegroup(
    name="output",
    data = glob(["*.csv", "*.json"], allow_empty=True),
    visibility = ["//:__subpackages__"],
)

exports_files(glob(allow_empty=True, include=["*.csv", "*.json"]))