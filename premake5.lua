workspace "Pine"
    architecture "x86_64"
    startproject "Pine"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    group "Library"
        include "pine"
    group ""

    group "Examples"
        -- include "examples"
    group ""
