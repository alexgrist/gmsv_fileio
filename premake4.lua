solution "gmsv_fileio"
	language "C++"
	location (os.get() .. "/" .. _ACTION)
	flags {"Symbols", "NoEditAndContinue", "NoPCH", "StaticRuntime", "EnableSSE"}
	targetdir ("build/" .. os.get())
	includedirs {"include/"}

	if (os.is("linux") or os.is("macosx")) then
		buildoptions {"-fPIC"}
	end

	configurations
	{
		"Release",
		"Debug"
	}

configuration "Release"
	defines { "NDEBUG" }
	flags{ "OptimizeSpeed", "FloatFast" }

configuration "Debug"
	defines { "_DEBUG" }

project "gmsv_fileio"
	defines { "GMMODULE" }
	files { "src/**.*", "include/**.*" }
	libdirs { "lib/" }
	kind "SharedLib"
	targetname( "gmsv_fileio" )

	if (os.is("Windows")) then
		links { "bootil_static" }
		targetsuffix "_win32"
	elseif (os.is("linux")) then
		links { "libbootil_static" }
		targetsuffix "_linux"
	end;