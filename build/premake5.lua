workspace "RayTracer"
  configurations {"Debug", "Release"}

project "RayTracer"
  kind "ConsoleApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"

  files {
    "../src/**.h",
    "../src/**.cpp",
    "../src/**.c"
  }

  filter "configurations:Debug"
    defines {"DEBUG"}
    symbols "On"

  filter "configurations:Release"
    defines {"NODEBUG"}
    optimize "On"
