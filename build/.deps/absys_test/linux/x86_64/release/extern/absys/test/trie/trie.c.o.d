{
    values = {
        "/usr/lib64/ccache/gcc",
        {
            "-m64",
            "-std=c11",
            "-Iextern/absys/include"
        }
    },
    depfiles_gcc = "trie.o: extern/absys/test/trie/trie.c extern/absys/include/absys/trie.h  extern/absys/include/absys/mem.h extern/absys/include/absys/defs.h  extern/absys/include/absys/vec.h extern/absys/include/absys/log.h  extern/absys/include/absys/utils.h extern/absys/include/debugbreak.h  extern/absys/include/absys/strstack.h  extern/absys/include/absys/objpool.h extern/absys/test/trie/trie.h  extern/absys/include/absys/test.h extern/absys/include/absys/str.h  extern/absys/include/absys/color.h\
",
    files = {
        "extern/absys/test/trie/trie.c"
    }
}