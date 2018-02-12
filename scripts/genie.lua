solution "MetaRayTrace"
    configurations { "Meta" }
    location("../.build/projects/" .. _ACTION)
    platforms { "x64" }
    debugdir ".."

    project "MetaRayTrace"
        targetname "MetaRaytrace"
        language "C++"
        kind "ConsoleApp"
        flags { "StaticRuntime" }

        files {
            "../Code/**.h",
            "../Code/**.cpp",
            "../scripts/**.lua",
        }

        configuration { "vs*" }
            buildoptions { "/bigobj" }

        configuration { "linux" }
            targetdir "../.build/bin/linux"
        configuration { "windows" }
            targetdir "../.build/bin/windows"
        configuration {}