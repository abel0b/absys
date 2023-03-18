filter "configurations:debug"
	optimize "Debug"

project "backtrace"
	kind "SharedLib"
	language "C"
   	cdialect "C99"
	includedirs { "backtrace" }
    files { "backtrace/alloc.c", "backtrace/read.c", "backtrace/backtrace.c", "backtrace/fileline.c", "backtrace/elf.c", "backtrace/simple.c", "backtrace/atomic.c", "backtrace/dwarf.c", "backtrace/fileline.c", "backtrace/posix.c", "backtrace/print.c", "backtrace/sort.c", "backtrace/state.c", "backtrace/config.h" }

function libbacktrace()
	links { "backtrace" }
end
