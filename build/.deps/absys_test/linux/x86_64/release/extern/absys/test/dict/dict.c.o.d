{
    values = {
        "/usr/lib64/ccache/gcc",
        {
            "-m64",
            "-std=c11",
            "-Iextern/absys/include"
        }
    },
    depfiles_gcc = "dict.o: extern/absys/test/dict/dict.c extern/absys/include/absys/dict.h  extern/absys/include/absys/strstack.h  extern/absys/include/absys/objpool.h extern/absys/include/absys/vec.h  extern/absys/include/absys/log.h extern/absys/include/absys/mem.h  extern/absys/include/absys/defs.h extern/absys/include/absys/utils.h  extern/absys/include/debugbreak.h extern/absys/test/dict/dict.h  extern/absys/include/absys/test.h extern/absys/include/absys/str.h  extern/absys/include/absys/color.h\
",
    files = {
        "extern/absys/test/dict/dict.c"
    }
}