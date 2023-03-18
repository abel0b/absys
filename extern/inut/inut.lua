project "inut"
    kind "StaticLib"
    language "C"
	cdialect "C99"
	includedirs { "include" }
    files { "include/**.h", "inut/**.h", "inut/**.c" }

function libinut()
    links "inut"
end

