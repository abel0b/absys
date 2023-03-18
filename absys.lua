filter "configurations:debug"
	optimize "Debug"

project "absys"
	kind "StaticLib"
	language "C"
   	cdialect "C99"
	defines { "ABSYS_DLL", "ABSYS_DLL_EXPORTS" }
	if os.getenv("ABSYS_NEXT") then
		includedirs { "include", "next" }
		files { "include/**.h", "absys/**.h", "absys/**.c" }
	else
		includedirs { "include" }
		files { "include/**.h", "absys/**.h", "absys/**.c" }
	end

function libabsys()
	links { "absys", "dl" }
end

