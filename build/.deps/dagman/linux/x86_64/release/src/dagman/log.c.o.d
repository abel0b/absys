{
    files = {
        "src/dagman/log.c"
    },
    values = {
        "/usr/lib64/ccache/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-O3",
            "-std=c11",
            "-Iinclude",
            "-Iextern/absys/include"
        }
    },
    depfiles_gcc = "log.o: src/dagman/log.c src/dagman/log.h extern/absys/include/absys/log.h\
"
}