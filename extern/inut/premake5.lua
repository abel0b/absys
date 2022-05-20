project "inut"
    kind "StaticLib"
    language "C"
    includedirs { "include" }
    files { "include/**.h", "inut/**.h", "inut/**.c" }
if os.host() == "windows" then
    defines { "WINDOWS=1", "_CRT_SECURE_NO_WARNINGS", "_CRT_NONSTDC_NO_WARNINGS" }
else
    defines { "UNIX=1", "_POSIX_C_SOURCE=200809L" }
end
