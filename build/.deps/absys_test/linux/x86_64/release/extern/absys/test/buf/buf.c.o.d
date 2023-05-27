{
    depfiles_gcc = "buf.o: extern/absys/test/buf/buf.c extern/absys/include/absys/vec.h  extern/absys/include/absys/log.h extern/absys/include/absys/mem.h  extern/absys/include/absys/defs.h extern/absys/include/absys/utils.h  extern/absys/include/debugbreak.h extern/absys/include/absys/buf.h  extern/absys/test/buf/buf.h extern/absys/include/absys/test.h  extern/absys/include/absys/str.h extern/absys/include/absys/color.h\
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
        "extern/absys/test/buf/buf.c"
    }
}