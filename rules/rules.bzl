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

# rule to run pylint on the current folder
def _pylint_check_impl(ctx):
    bash_script = ctx.outputs.executable

    # find all the python files under the current folder and pass to pylint
    # $BUILD_WORKSPACE_DIRECTORY gets cwd, and ctx.label.package gets the path relative to the root (workspace) dir
    content_str = "#!/usr/bin/env bash\n" + "pylint --rcfile=$BUILD_WORKSPACE_DIRECTORY/.pylintrc " + "$(find $BUILD_WORKSPACE_DIRECTORY/" + ctx.label.package + " -type f -name '*.py')\n"
    contents = (content_str)

    ctx.actions.write(
      output = bash_script,
      is_executable = True,
      content = contents,
    )

    return [DefaultInfo(
        executable = bash_script,
        files = depset([bash_script]),
    )]

pylint_check = rule(
    implementation = _pylint_check_impl,
    executable = True,
)