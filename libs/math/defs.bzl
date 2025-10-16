def _gen_stats_impl(ctx):
    out = ctx.actions.declare_file("output.json")

    # run cc_binary here
    ctx.actions.run(
        inputs = ctx.files.data,
        outputs = [out],
        # pass input and output file name as arguments
        arguments = [ctx.attr.data[0].path, out.path],
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