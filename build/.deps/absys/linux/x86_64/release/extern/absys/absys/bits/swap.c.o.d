{
    files = {
        "extern/absys/absys/bits/swap.c"
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
    depfiles_gcc = "swap.o: extern/absys/absys/bits/swap.c extern/absys/include/absys/bits.h\
"
}