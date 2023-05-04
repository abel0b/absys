option("absys-enable-test")
	set_default(false)
	set_showmenu(true)
	set_description("Enable absys test target")

target("absys")
	if is_mode("debug") then
		set_symbols("debug")
		set_optimize("none")
	else
		set_symbols("hidden")
		set_optimize("fastest")
	end

	if is_plat("windows") then
		add_defines("LINUX=1")
	end

	if is_plat("windows") then
		add_defines("WINDOWS=1", "_CRT_SECURE_NO_WARNINGS", "_CRT_NONSTDC_NO_WARNINGS")
	else
		add_defines("UNIX=1", "_POSIX_C_SOURCE=200809L")
	end

	--add_defines("ABSYS_DLL", "ABSYS_DLL_EXPORTS")
	--on_load(function (target)
	--	target:add("defines", "ABSYS_DLL")
	--end)

	add_includedirs("include", {public = true})
	set_kind("static")
	if is_plat("linux") then
		add_defines("LINUX")
	end
	if is_plat("windows") then
		add_defines("WINDOWS")
	end
	if is_plat("linux", "macosx") then
		add_defines("UNIX")
	end
	add_files("absys/**.c")
	--add_files("next/**.c")

if has_config("absys-enable-test") then
	target("absys_test")
		add_deps("absys")
		add_includedirs("include")
		set_kind("binary")
		add_files("test/**.c")
end
