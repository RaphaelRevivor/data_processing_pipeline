load("//rules:rules.bzl", "pylint_test")

# This is actually not hermetic, but the easiest way
genrule(
    name = "get_commit_sha",
    outs = ["version.txt"],
    cmd = "git rev-parse HEAD 2>&1 | tee $@",
    local = True,  # allows access to .git
)