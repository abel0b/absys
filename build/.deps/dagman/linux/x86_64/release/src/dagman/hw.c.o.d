{
    files = {
        "src/dagman/hw.c"
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
    depfiles_gcc = "hw.o: src/dagman/hw.c include/dagman/hw.h  extern/absys/include/absys/para.h\
"
}