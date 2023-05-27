{
    depfiles_gcc = "queue.o: extern/absys/absys/queue/queue.c  extern/absys/include/absys/queue.h extern/absys/include/absys/log.h  extern/absys/include/absys/mem.h extern/absys/include/absys/defs.h  extern/absys/include/absys/utils.h extern/absys/include/debugbreak.h\
",
    files = {
        "extern/absys/absys/queue/queue.c"
    },
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