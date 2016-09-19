-- premake5.lua
workspace "OpenGL"
    configurations { "Debug", "Release" }
    location "build"

local name = "triangle"
project(name)
    local target = "bin/" .. name .. "/%{cfg.buildcfg}"
    targetdir(target)
    kind "WindowedApp"
    language "C++"
    links{ "SDL2", "SDL2main", "SDL2_image", "SDL2_ttf", "SDL2_mixer" }
    includedirs { "core", "core/**", "glad/include/" }
    files({ "core/**.cpp", name .. "/**.h", name .. "/**.cpp", "glad/src/glad.c" })

    filter "configurations:Debug"
        defines "DEBUG"
        flags "Symbols"

    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"

    configuration { "linux", "gmake" }
        links{ "GL", "dl" } -- libdl is required by glad on non-windows platforms
        buildoptions { "`sdl2-config --cflags`", "-std=c++11" }
        linkoptions "`sdl2-config --libs`"
        -- Copy shaders to the output directory
        postbuildcommands("cp -r ../" .. name .."/shaders ../bin/" .. name .. "/%{cfg.buildcfg}")

	configuration { "windows" }
		links "OpenGL32.lib" -- link OpenGL on windows
		local sdl2_path = os.getenv("SDL2_PATH")
		local sdl2_include = (sdl2_path or "") .. "/include"
		local sdl2_lib = (sdl2_path or "") .. "/lib/x86"
		local glm_path = os.getenv("GLM_PATH")
		debugdir(target)
		includedirs { sdl2_include, glm_path }
		libdirs { sdl2_lib }
		-- Post build events in Visual Studio to copy shaders to the output directory
		postbuildcommands({
		"xcopy /E /Y /I \"$(SolutionDir)../" .. name .. "/shaders\" \"$(TargetDir)\"",
		"xcopy /E /Y /I \"" .. (string.gsub(sdl2_lib, "/", "\\") or "") .. "\\*.dll" .. "\" \"$(TargetDir)\"" })

