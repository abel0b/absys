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
        "extern/absys/absys/fs/filebuf.c"
    },
    depfiles_gcc = "extern/absys/build/.objs/absys/linux/x86_64/debug/extern/absys/absys/fs/__cpp_filebuf.c.c:   extern/absys/absys/fs/filebuf.c extern/absys/include/absys/filebuf.h   extern/absys/include/absys/vec.h extern/absys/include/absys/log.h   extern/absys/include/absys/mem.h extern/absys/include/absys/defs.h   extern/absys/include/absys/utils.h extern/absys/include/debugbreak.h   extern/absys/include/absys/buf.h\
"
}