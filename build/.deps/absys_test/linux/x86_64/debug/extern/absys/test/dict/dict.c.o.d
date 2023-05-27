{
    values = {
        "clang",
        {
            "-Qunused-arguments",
            "-m64",
            "-std=c11",
            "-Iextern/absys/include"
        }
    },
    files = {
        "extern/absys/test/dict/dict.c"
    },
    depfiles_gcc = "extern/absys/build/.objs/absys_test/linux/x86_64/debug/extern/absys/test/dict/__cpp_dict.c.c:   extern/absys/test/dict/dict.c extern/absys/include/absys/dict.h   extern/absys/include/absys/strstack.h   extern/absys/include/absys/objpool.h extern/absys/include/absys/vec.h   extern/absys/include/absys/log.h extern/absys/include/absys/mem.h   extern/absys/include/absys/defs.h extern/absys/include/absys/utils.h   extern/absys/include/debugbreak.h extern/absys/test/dict/dict.h   extern/absys/include/absys/test.h extern/absys/include/absys/str.h   extern/absys/include/absys/color.h\
"
}