{
    values = {
        "/usr/lib64/ccache/gcc",
        {
            "-m64",
            "-std=c11",
            "-Iextern/absys/include"
        }
    },
    depfiles_gcc = "main.o: extern/absys/test/main.c extern/absys/include/absys/test.h  extern/absys/include/absys/str.h extern/absys/include/absys/vec.h  extern/absys/include/absys/log.h extern/absys/include/absys/mem.h  extern/absys/include/absys/defs.h extern/absys/include/absys/utils.h  extern/absys/include/debugbreak.h extern/absys/include/absys/color.h  extern/absys/test/bits/bits.h extern/absys/test/buf/buf.h  extern/absys/test/dict/dict.h extern/absys/test/filebuf/filebuf.h  extern/absys/test/hook/hook.h extern/absys/test/set/set.h  extern/absys/test/trie/trie.h extern/absys/test/vec/vec.h  extern/absys/test/list/list.h\
",
    files = {
        "extern/absys/test/main.c"
    }
}