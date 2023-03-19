require "tools/utils"

local config = {}
config.backtrace = false
if fexists("config.lua") then
    local uconfig = require "config"
    merge_tables(config, uconfig)
end

workspace "absys"
    configurations { "debug", "release", "debug-vg" }

    if os.host() == "windows" then
        defines { "WINDOWS=1", "_CRT_SECURE_NO_WARNINGS", "_CRT_NONSTDC_NO_WARNINGS" }
    else
        defines { "UNIX=1", "_POSIX_C_SOURCE=200809L" }
    end

    filter "configurations:debug or debug-vg"
 	    defines { "DEBUG=1" }
        symbols "On"

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
            linkoptions { "-fsanitize=address,leak,undefined" }
            defines { "DEBUG_SAN=1" }
        filter { "configurations:debug or debug-vg", "toolset:clang or gcc" }
            buildoptions { "-g" }
    end

    include "absys.lua"
	if config.backtrace then
        include "extern/backtrace.lua"
    end

    project "test"
        kind "ConsoleApp"
        language "C"
    	cdialect "C99"
        buildoptions { "-funwind-tables", "-fasynchronous-unwind-tables", "-fno-omit-frame-pointer", "-fno-optimize-sibling-calls" }
        includedirs { "include" }
	    defines { "ABSYS_DLL" }
        files { "include/**.h", "test/**.c" }
	    use_absys {}
	    if config.backtrace then
            use_backtrace {}
        end

newoption {
    trigger = "prefix",
    value = "/usr/local",
    description = "Install prefix",
    default = "/usr/local",
}

function install_action (prefix)
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
    trigger = "gen-config",
    description = "Generate config.lua",
    execute = function ()
        config = io.open("config.lua", "w")
        config:write("local config = {}\n")
        config:write("config.foo = 42\n")
        config:write("return config\n")
        config:close()
    end
}

newaction {
    trigger = "test",
    description = "Run test suite",
    execute = function ()
	os.execute("bin/debug/test")
    end
}

