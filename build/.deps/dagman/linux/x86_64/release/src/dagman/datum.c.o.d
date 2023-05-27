{
    depfiles_gcc = "datum.o: src/dagman/datum.c include/dagman/datum.h  extern/absys/include/absys/vec.h extern/absys/include/absys/log.h  extern/absys/include/absys/mem.h extern/absys/include/absys/defs.h  extern/absys/include/absys/utils.h extern/absys/include/debugbreak.h  extern/absys/include/absys/list.h extern/absys/include/absys/config.h  extern/absys/include/absys/objpool.h include/dagman/task.h  extern/absys/include/absys/buf.h include/dagman/rt.h include/dagman/hw.h  include/dagman/worker.h\
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
        "src/dagman/datum.c"
    }
}