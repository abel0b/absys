{
    depfiles_gcc = "proc.o: extern/absys/absys/subproc/proc.c  extern/absys/include/absys/proc.h extern/absys/include/absys/defs.h  extern/absys/include/absys/log.h extern/absys/include/absys/str.h  extern/absys/include/absys/vec.h extern/absys/include/absys/mem.h  extern/absys/include/absys/utils.h extern/absys/include/debugbreak.h\
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
        "extern/absys/absys/subproc/proc.c"
    }
}