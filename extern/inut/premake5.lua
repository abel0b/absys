project "inut"
    kind "StaticLib"
    language "C"
if os.host() == "windows" then
    defines { "WINDOWS=1", "_CRT_SECURE_NO_WARNINGS", "_CRT_NONSTDC_NO_WARNINGS" }
else
    defines { "UNIX=1", "_POSIX_C_SOURCE=200809L" }
end
    includedirs { "include" }
    files { "include/**.h", "inut/**.h", "inut/**.c" }


function libinut()
   links "inut"
end

