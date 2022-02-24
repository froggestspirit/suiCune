workspace "suiCune"
	location ".\\build\\"

	targetdir "%{wks.location}\\bin\\%{cfg.buildcfg}\\"
	objdir "%{wks.location}\\obj\\%{cfg.buildcfg}\\%{prj.name}\\"
	buildlog "%{wks.location}\\obj\\%{cfg.buildcfg}\\%{prj.name}.log"

	largeaddressaware "on"
	editandcontinue "off"
	staticruntime "on"

	systemversion "latest"
	characterset "unicode"
	architecture "x86"
	warnings "extra"
	
	platforms {
		"x86",
	}

	configurations {
		"Release",
		"Debug",
	}

	filter "Release"
		defines "NDEBUG"
		optimize "debug"
		runtime "debug"
		symbols "on"

	filter "Debug"
		defines "DEBUG"
		optimize "debug"
		runtime "debug"
		symbols "on"

	project "suiCune"
		targetname "suiCune"
		language "c++"
		kind "windowedapp"
		warnings "off"

		-- Not sure if this will work on other platforms other than visual studio
		nuget { "sdl2.nuget:2.0.20", "sdl2.nuget.redist:2.0.20" }
		
		files {
			".\\**.c",
			".\\**.h",
		}