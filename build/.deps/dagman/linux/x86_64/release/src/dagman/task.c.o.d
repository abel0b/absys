{
    depfiles_gcc = "task.o: src/dagman/task.c include/dagman/task.h  extern/absys/include/absys/buf.h extern/absys/include/absys/vec.h  extern/absys/include/absys/log.h extern/absys/include/absys/mem.h  extern/absys/include/absys/defs.h extern/absys/include/absys/utils.h  extern/absys/include/debugbreak.h extern/absys/include/absys/list.h  extern/absys/include/absys/config.h extern/absys/include/absys/objpool.h  include/dagman/datum.h include/dagman/rt.h include/dagman/hw.h  include/dagman/worker.h src/dagman/log.h\
",
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
    files = {
        "src/dagman/task.c"
    }
}