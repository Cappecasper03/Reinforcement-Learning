sfmlPath = "../../sfml"

filter {}
    includedirs { sfmlPath.."/include" }
    libdirs { sfmlPath.."/lib" }

filter "configurations:Debug"
    links { "sfml-graphics-d", "sfml-window-d", "sfml-system-d" }
    
filter "configurations:not Debug"
    links { "sfml-graphics", "sfml-window", "sfml-system" }