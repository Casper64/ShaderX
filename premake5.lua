workspace "ShaderX"
	architecture "x64"
	startproject "ShaderX"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-$%{cfg.architecture}"
-- Include directories relative to the root folder
IncludeDir = {}
IncludeDir["GLFW"] = "ShaderX/vendor/GLFW/include"
IncludeDir["glad"] = "ShaderX/vendor/glad/include"
IncludeDir["ImGui"] = "ShaderX/vendor/imgui"
IncludeDir["glm"] = "ShaderX/vendor/glm"

include "ShaderX/vendor/GLFW"
include "ShaderX/vendor/glad"
include "ShaderX/vendor/imgui"

project "ShaderX"
	location "ShaderX"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "ShaderX/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/src/user",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	libdirs
	{
	}

	links
	{
		"GLFW",
		"glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "BUILD_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "BUILD_DIST"
		buildoptions "/MD"
		optimize "On"
		
