# rule to generate statistics
def _gen_stats_impl(ctx):
    out = ctx.actions.declare_file("output.json")

    # run cc_binary here
    ctx.actions.run(
        inputs = ctx.files.data,
        outputs = [out],
        # pass input and output file name as arguments
        arguments = [ctx.files.data[0].path, out.path],
        executable = ctx.executable.tool,
        tools = [ctx.executable.tool],
        use_default_shell_env = True,
    )

    return [DefaultInfo(
        files = depset([out]),
    )]

gen_stats = rule(
    implementation = _gen_stats_impl,
    attrs = {
        "tool": attr.label(executable = True, cfg = "exec"),
        "data": attr.label_list(allow_files = True),
    },
)

# rule to run pylint on the current folder,
# this rule can only see python files in sub-dirs that does not contain BUILD file
def _pylint_test_impl(ctx):
    bash_script = ctx.outputs.executable

    # directly pass the pylintrc config here
    cmds = ("pylint --persistent=n --ignore=tests,build,dist,__pycache__,__init__.py"
           + " --disable=missing-docstring,too-few-public-methods,too-many-arguments,"
           + "too-many-locals,too-many-instance-attributes,too-many-return-statements,"
           + "too-many-branches,too-many-statements,too-many-lines,"
           + "invalid-name,redefined-outer-name,line-too-long,import-error"
           + " --max-line-length=100"
           + " --output-format=colorized"
           + " --score=no")

    for item in ctx.files.data:
      cmds += " $RUNFILES_DIR/$TEST_WORKSPACE/" + item.path

    contents = "#!/usr/bin/env bash\n" + cmds + "\n"

    ctx.actions.write(
      output = bash_script,
      is_executable = True,
      content = contents,
    )

    return [DefaultInfo(
        executable = bash_script,
        files = depset([bash_script]),
        runfiles = ctx.runfiles(files = ctx.files.data)
    )]

pylint_test = rule(
    implementation = _pylint_test_impl,
    executable = True,
    test = True,
    attrs = {
        "data": attr.label_list(allow_files = True),
    },
)