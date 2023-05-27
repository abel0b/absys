{
    files = {
        "extern/absys/test/list/list.c"
    },
    depfiles_gcc = "list.o: extern/absys/test/list/list.c extern/absys/include/absys/test.h  extern/absys/include/absys/str.h extern/absys/include/absys/vec.h  extern/absys/include/absys/log.h extern/absys/include/absys/mem.h  extern/absys/include/absys/defs.h extern/absys/include/absys/utils.h  extern/absys/include/debugbreak.h extern/absys/include/absys/color.h  extern/absys/include/absys/list.h extern/absys/include/absys/config.h  extern/absys/include/absys/objpool.h extern/absys/test/list/list.h\
",
    values = {
        "/usr/lib64/ccache/gcc",
        {
            "-m64",
            "-std=c11",
            "-Iextern/absys/include"
        }
    }
}