filter "configurations:debug"
	optimize "Debug"

project "absys"
	kind "SharedLib"
	language "C"
   	cdialect "C99"
	defines { "ABSYS_DLL", "ABSYS_DLL_EXPORTS" }
	includedirs { "include" }
	files { "include/**.h", "absys/**.h", "absys/**.c" }

function use_absys()
	links { "absys" }
    	if os.host() ~= "windows" then
		links { "dl" }
	end
end

