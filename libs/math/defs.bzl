def _gen_stats_impl(ctx):
    out = ctx.actions.declare_file("output.json")
    #print("LEN CTX DATA: " + str(len(ctx.attr.data)))
    #print(type(ctx.attr.data[0]))
    data_files = []
    for t in ctx.attr.data:
        if DefaultInfo in t:
            data_files.extend(t[DefaultInfo].files.to_list())
            print("Extended data files with defaultinfo: " )
            print(t[DefaultInfo].data_runfiles.files.to_list())
            print(t[DefaultInfo].default_runfiles.files.to_list())
            #print(t[DefaultInfo].files_to_run.to_list())

        else:
            fail("Target %s does not provide DefaultInfo" % t.label)
 
    print("Collected data files:", [f.path for f in data_files])

    #first_data = ctx.files.data[0][0] if type(ctx.attr.data) == list else ctx.files.data[0]

    # run cc_binary here
    ctx.actions.run(
        inputs = ctx.files.data,
        outputs = [out],
        # pass input and output file name as arguments
        arguments = [collect_files(ctx.attr.data)[0].path, out.path],
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

def collect_files(targets):
    files = []
    for t in targets:
        if DefaultInfo in t:
            info = t[DefaultInfo]
            files.extend(info.files.to_list())
            files.extend(info.default_runfiles.files.to_list())
            files.extend(info.data_runfiles.files.to_list())
    
    print(files)
    return files