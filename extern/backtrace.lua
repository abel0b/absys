project "backtrace"
    prebuildcommands {
        "test -f backtrace/config.h || (cd backtrace && ./configure)"
    }
    kind "SharedLib"
    language "C"
    cdialect "C99"
    includedirs { "backtrace" }
    files { "backtrace/alloc.c", "backtrace/read.c", "backtrace/backtrace.c", "backtrace/fileline.c", "backtrace/elf.c", "backtrace/simple.c", "backtrace/atomic.c", "backtrace/dwarf.c", "backtrace/fileline.c", "backtrace/posix.c", "backtrace/print.c", "backtrace/sort.c", "backtrace/state.c", "backtrace/config.h" }

function use_backtrace()
	links { "backtrace" }
end
