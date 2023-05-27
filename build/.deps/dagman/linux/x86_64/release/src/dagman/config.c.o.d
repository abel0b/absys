{
    files = {
        "src/dagman/config.c"
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
    depfiles_gcc = "config.o: src/dagman/config.c include/dagman/config.h  extern/absys/include/absys/para.h\
"
}