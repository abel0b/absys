{
    files = {
        "extern/absys/absys/para/nproc.c"
    },
    depfiles_gcc = "nproc.o: extern/absys/absys/para/nproc.c  extern/absys/include/absys/para.h\
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