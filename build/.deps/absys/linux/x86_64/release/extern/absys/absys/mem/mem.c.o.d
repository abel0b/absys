{
    files = {
        "extern/absys/absys/mem/mem.c"
    },
    depfiles_gcc = "mem.o: extern/absys/absys/mem/mem.c extern/absys/include/absys/mem.h  extern/absys/include/absys/defs.h extern/absys/include/absys/log.h\
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
    }
}