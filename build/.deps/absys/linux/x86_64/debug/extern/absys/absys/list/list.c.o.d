{
    values = {
        "clang",
        {
            "-Qunused-arguments",
            "-m64",
            "-g",
            "-O0",
            "-std=c11",
            "-Iextern/absys/include",
            "-DUNIX=1",
            "-D_POSIX_C_SOURCE=200809L",
            "-DLINUX",
            "-DUNIX"
        }
    },
    files = {
        "extern/absys/absys/list/list.c"
    },
    depfiles_gcc = "extern/absys/build/.objs/absys/linux/x86_64/debug/extern/absys/absys/list/__cpp_list.c.c:   extern/absys/absys/list/list.c extern/absys/include/absys/list.h   extern/absys/include/absys/config.h   extern/absys/include/absys/objpool.h extern/absys/include/absys/vec.h   extern/absys/include/absys/log.h extern/absys/include/absys/mem.h   extern/absys/include/absys/defs.h extern/absys/include/absys/utils.h   extern/absys/include/debugbreak.h\
"
}