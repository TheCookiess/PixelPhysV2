-- Defines solution
workspace "falling-sand"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

-- Defines output directories
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Defines configuration
project "app"
    location "build"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"
    targetdir ("bin/" .. outputdir)
    objdir ("bin-int/" .. outputdir)

    -- Link Code Files
    files { 
        "app/src/**.cpp", 
        "app/include/**.h", 
        "lib/imgui/src/**.cpp",
        "lib/imgui/include/**.h",
    }

    -- Defines libraries to link
    links {
        "SDL2",
        "SDL2_image",
        "opengl32",
    }

    -- Links .lib files
    libdirs {
        "lib/SDL2/lib/x64",
        "lib/SDL2_IMAGE/lib/x64",
    }

    -- Includes directories for the compiler to search
    includedirs {
        "app/include",
        "lib/boost/",
        "lib/imgui/include",
        "lib/SDL2/include",
        "lib/SDL2_IMAGE/include",
    }

    postbuildcommands {
        "{COPYFILE} %[lib/SDL2/lib/x64/SDL2.dll] %[bin/" .. outputdir .. "]",
        "{COPYFILE} %[lib/SDL2_IMAGE/lib/x64/SDL2_image.dll] %[bin/" .. outputdir .. "]",
    }

    filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"
