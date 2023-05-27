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
        "extern/absys/absys/uid/uid.c"
    },
    depfiles_gcc = "extern/absys/build/.objs/absys/linux/x86_64/debug/extern/absys/absys/uid/__cpp_uid.c.c:   extern/absys/absys/uid/uid.c extern/absys/include/absys/uid.h   extern/absys/include/absys/defs.h extern/absys/include/absys/time.h   extern/absys/include/absys/log.h\
"
}