{
    depfiles_gcc = "time.o: extern/absys/absys/time/time.c extern/absys/include/absys/time.h  extern/absys/include/absys/defs.h extern/absys/include/absys/log.h\
",
    values = {
        "/usr/lib64/ccache/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-O3",
            "-std=c11",
            "-Iextern/absys/include",
            "-DUNIX=1",
            "-D_POSIX_C_SOURCE=200809L",
            "-DLINUX",
            "-DUNIX"
        }
    },
    files = {
        "extern/absys/absys/time/time.c"
    }
}