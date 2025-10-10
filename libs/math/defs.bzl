def _gen_stats_impl(ctx):
    loc = ctx.label.workspace_name + "/libs/math/" + ctx.attr.tool.label.name

    launcher_script = (
        "#!/usr/bin/env bash\n"
        + "set -euo pipefail\n"
        + "SELF=\"$0\"\n"
        + "RUNFILES_DIR=$SELF.runfiles/_main\n"
        + "if [[ ! -d \"$RUNFILES_DIR\" ]]; then\n"
        + "  RUNFILES_DIR=\"${SELF}.runfiles\"\n"
        + "fi\n"
        # export this so the cc_binary uses the same runfiles dir
        + "export RUNFILES_DIR\n"
        + "BIN=$RUNFILES_DIR" + loc + "\n"
        + "exec $BIN " + "/\"$@\"\n"
    )

    # Create a launcher script that forwards the arguments to cc_binary.
    ctx.actions.write(
        output = ctx.outputs.executable,
        content = launcher_script,
        is_executable = True,
    )
    return [DefaultInfo(
        executable = ctx.outputs.executable,
        runfiles = ctx.runfiles(files = ctx.files.data + [ctx.executable.tool]),
    )]

gen_stats = rule(
    implementation = _gen_stats_impl,
    executable = True,
    attrs = {
        "tool": attr.label(executable = True, cfg = "exec"),
        "data": attr.label_list(allow_files = True),
    },
)