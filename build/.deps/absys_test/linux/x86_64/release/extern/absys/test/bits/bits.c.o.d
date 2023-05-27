{
    depfiles_gcc = "bits.o: extern/absys/test/bits/bits.c extern/absys/include/absys/test.h  extern/absys/include/absys/str.h extern/absys/include/absys/vec.h  extern/absys/include/absys/log.h extern/absys/include/absys/mem.h  extern/absys/include/absys/defs.h extern/absys/include/absys/utils.h  extern/absys/include/debugbreak.h extern/absys/include/absys/color.h  extern/absys/test/bits/bits.h\
",
    values = {
        "/usr/lib64/ccache/gcc",
        {
            "-m64",
            "-std=c11",
            "-Iextern/absys/include"
        }
    },
    files = {
        "extern/absys/test/bits/bits.c"
    }
}