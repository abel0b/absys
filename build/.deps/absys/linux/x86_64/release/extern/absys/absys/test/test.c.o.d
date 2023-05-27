{
    depfiles_gcc = "test.o: extern/absys/absys/test/test.c extern/absys/include/absys/test.h  extern/absys/include/absys/str.h extern/absys/include/absys/vec.h  extern/absys/include/absys/log.h extern/absys/include/absys/mem.h  extern/absys/include/absys/defs.h extern/absys/include/absys/utils.h  extern/absys/include/debugbreak.h extern/absys/include/absys/color.h  extern/absys/include/absys/time.h\
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
        "extern/absys/absys/test/test.c"
    }
}