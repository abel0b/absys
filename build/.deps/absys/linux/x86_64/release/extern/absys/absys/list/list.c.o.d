{
    files = {
        "extern/absys/absys/list/list.c"
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
    },
    depfiles_gcc = "list.o: extern/absys/absys/list/list.c extern/absys/include/absys/list.h  extern/absys/include/absys/config.h extern/absys/include/absys/objpool.h  extern/absys/include/absys/vec.h extern/absys/include/absys/log.h  extern/absys/include/absys/mem.h extern/absys/include/absys/defs.h  extern/absys/include/absys/utils.h extern/absys/include/debugbreak.h\
"
}