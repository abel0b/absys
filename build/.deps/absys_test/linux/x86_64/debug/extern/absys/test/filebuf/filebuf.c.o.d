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
        "extern/absys/test/filebuf/filebuf.c"
    },
    depfiles_gcc = "extern/absys/build/.objs/absys_test/linux/x86_64/debug/extern/absys/test/filebuf/__cpp_filebuf.c.c:   extern/absys/test/filebuf/filebuf.c   extern/absys/include/absys/filebuf.h extern/absys/include/absys/vec.h   extern/absys/include/absys/log.h extern/absys/include/absys/mem.h   extern/absys/include/absys/defs.h extern/absys/include/absys/utils.h   extern/absys/include/debugbreak.h extern/absys/include/absys/buf.h   extern/absys/test/filebuf/filebuf.h extern/absys/include/absys/test.h   extern/absys/include/absys/str.h extern/absys/include/absys/color.h\
"
}