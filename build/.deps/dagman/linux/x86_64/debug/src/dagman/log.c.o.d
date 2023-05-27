{
    values = {
        "clang",
        {
            "-Qunused-arguments",
            "-m64",
            "-g",
            "-O0",
            "-std=c11",
            "-Iinclude",
            "-Iextern/absys/include"
        }
    },
    files = {
        "src/dagman/log.c"
    },
    depfiles_gcc = "extern/absys/build/.objs/dagman/linux/x86_64/debug/src/dagman/__cpp_log.c.c:   src/dagman/log.c src/dagman/log.h extern/absys/include/absys/log.h\
"
}