workspace "absys"
    configurations { "debug", "release", "debug-vg" }

    if os.host() == "windows" then
        defines { "WINDOWS=1", "_CRT_SECURE_NO_WARNINGS", "_CRT_NONSTDC_NO_WARNINGS" }
    else
        defines { "UNIX=1", "_POSIX_C_SOURCE=200809L" }
    end

    filter "configurations:debug or debug-vg"
 	defines { "DEBUG=1" }

    filter "configurations:release"
 	defines { "DEBUG=0" }
	optimize "On"

    filter { "configurations:release", "toolset:clang or gcc" }
 	buildoptions { "-Wall -Wextra" }
	visibility "Hidden"

    filter { "configurations:debug", "toolset:clang or gcc" }
 	buildoptions { "-pedantic" }

    filter "configurations:debug"
	optimize "Debug"

    if os.host() == "linux" then
 	filter { "configurations:debug", "toolset:clang" }
        buildoptions { "-funwind-tables", "-fasynchronous-unwind-tables", "-fno-omit-frame-pointer", "-fno-optimize-sibling-calls" }
	--linkoptions { "-fsanitize=address,leak,undefined", "-Wl,--export-dynamic" }
	defines { "DEBUG_SAN=1" }
	filter { "configurations:debug or debug-vg", "toolset:clang or gcc" }
	buildoptions { "-ggdb3" }
    end

    include "extern/inut/inut.lua"
    include "absys.lua"

    project "test"
        kind "ConsoleApp"
        language "C"
	libdirs {"/cm/shared/modules/intel/skylake/compiler/gcc/12.2.0/lib64"}
    	cdialect "C99"
        buildoptions { "-funwind-tables", "-fasynchronous-unwind-tables", "-fno-omit-frame-pointer", "-fno-optimize-sibling-calls" }
	--linkoptions { "-fsanitize=address,leak,undefined", "-Wl,--export-dynamic" }
        includedirs { "include", "extern/inut/include" }
	defines { "ABSYS_DLL" }
	libabsys {}
	libinut {}
        files { "include/**.h", "test/**.c" }

newoption {
    trigger = "prefix",
    value = "/usr/local",
    description = "Install prefix",
    default = "/usr/local",
}

function install_action (prefix)
    libdir = prefix .. "/lib/"
    os.mkdir(libdir)
    if os.host() == "windows" then
        assert(os.copyfile("bin/release/absys.lib", libdir .. "absys.lib"))
    else
        assert(os.copyfile("bin/release/libabsys.a", libdir .. "libabsys.a"))
    end
end

newaction {
    trigger = "install",
    description = "Install absys",
    execute = function ()
        install_action(_OPTIONS["prefix"])
    end
}

newaction {
    trigger = "gen-compile-flags",
    description = "Generate compile_flags.txt for clangd",
    execute = function ()
        flags = io.open("compile_flags.txt", "w")
        flags:write("-Wall\n")
        flags:write("-Wextra\n")
        flags:write("-Iinclude\n")
        flags:close()
    end
}

newaction {
    trigger = "test",
    description = "Run test suite",
    execute = function ()
	os.execute("bin/debug/test")
    end
}

