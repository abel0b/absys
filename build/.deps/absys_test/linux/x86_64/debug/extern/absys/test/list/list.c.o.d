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
        "extern/absys/test/list/list.c"
    },
    depfiles_gcc = "extern/absys/build/.objs/absys_test/linux/x86_64/debug/extern/absys/test/list/__cpp_list.c.c:   extern/absys/test/list/list.c extern/absys/include/absys/test.h   extern/absys/include/absys/str.h extern/absys/include/absys/vec.h   extern/absys/include/absys/log.h extern/absys/include/absys/mem.h   extern/absys/include/absys/defs.h extern/absys/include/absys/utils.h   extern/absys/include/debugbreak.h extern/absys/include/absys/color.h   extern/absys/include/absys/list.h extern/absys/include/absys/config.h   extern/absys/include/absys/objpool.h extern/absys/test/list/list.h\
"
}