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
        "src/dagman/hw.c"
    },
    depfiles_gcc = "extern/absys/build/.objs/dagman/linux/x86_64/debug/src/dagman/__cpp_hw.c.c:   src/dagman/hw.c include/dagman/hw.h extern/absys/include/absys/para.h\
"
}