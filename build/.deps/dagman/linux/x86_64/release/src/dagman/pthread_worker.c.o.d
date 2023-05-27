{
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
    depfiles_gcc = "pthread_worker.o: src/dagman/pthread_worker.c include/dagman/worker.h  extern/absys/include/absys/vec.h extern/absys/include/absys/log.h  extern/absys/include/absys/mem.h extern/absys/include/absys/defs.h  extern/absys/include/absys/utils.h extern/absys/include/debugbreak.h  include/dagman/task_queue.h include/dagman/task.h  extern/absys/include/absys/buf.h extern/absys/include/absys/list.h  extern/absys/include/absys/config.h extern/absys/include/absys/objpool.h  include/dagman/datum.h include/dagman/rt.h include/dagman/hw.h  src/dagman/log.h\
",
    files = {
        "src/dagman/pthread_worker.c"
    }
}