project "Pine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin/int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "source/**.cpp",
        "include/**.hpp"
    }

    includedirs
    {
        "include"
    }
