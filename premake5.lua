workspace "CrystalX"
    architecture "x64"
    
    configurations {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.system}_%{cfg.architecture}-%{cfg.buildcfg}"

project "CrystalX"
    location "CrystalX"
    kind "SharedLib"
    language "C++"
    
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/build_temp/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{wks.location}/%{prj.name}/src/",
        "%{wks.location}/%{prj.name}/thirdparty_for_CrystalX/spdlog/include/"
    }
    
    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"

        staticruntime "Off"
        buildoptions { "/utf-8" }

        defines {
            "CRYSTALX_WINDOWS",
            "CRYSTALX_BUILD_DLL"
        }
    
    filter "configurations:Debug"
        defines "CRYSTALX_DEBUG"
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        defines "CRYSTALX_RELEASE"
        optimize "On"
        runtime "Release"

    filter "configurations:Dist"
        defines "CRYSTALX_DIST"
        optimize "On"
        runtime "Release"

project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"
    
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/build_temp/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{wks.location}/CrystalX/src/",
        "%{wks.location}/CrystalX/thirdparty_for_CrystalX/spdlog/include/"
    }

    links {
        "CrystalX"
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"
        staticruntime "Off"
        buildoptions { "/utf-8" }

        defines {
            "CRYSTALX_WINDOWS"
        }
    
    filter "configurations:Debug"
        defines "CRYSTALX_DEBUG"
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        defines "CRYSTALX_RELEASE"
        optimize "On"
        runtime "Release"

    filter "configurations:Dist"
        defines "CRYSTALX_DIST"
        optimize "On"
        runtime "Release"