cmake_minimum_required(VERSION 3.10)
project(NewtonPolygon)

# -------------------- C++ Standard --------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# -------------------- Source and Include --------------------
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

# -------------------- Static SFML --------------------
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# -------------------- Executable --------------------
add_executable(NewtonPolygon ${SOURCES})

# -------------------- Link SFML --------------------
if(SFML_STATIC_LIBRARIES)
    # Link SFML static libraries
    target_link_libraries(NewtonPolygon
        sfml-graphics-s
        sfml-window-s
        sfml-system-s
    )

    # Add extra dependencies required for static linking
    if(WIN32)
        target_link_libraries(NewtonPolygon
            opengl32
            freetype
            winmm
            gdi32
            ws2_32
        )
    elseif(APPLE)
        find_library(COCOA_LIBRARY Cocoa REQUIRED)
        find_library(OPENGL_LIBRARY OpenGL REQUIRED)
        find_library(IOKIT_LIBRARY IOKit REQUIRED)
        find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
        target_link_libraries(NewtonPolygon
            ${COCOA_LIBRARY}
            ${OPENGL_LIBRARY}
            ${IOKIT_LIBRARY}
            ${COREVIDEO_LIBRARY}
        )
    elseif(UNIX)
        target_link_libraries(NewtonPolygon
            pthread
            X11
            GL
            freetype
            dl
        )
    endif()
else()
    # Dynamic linking (if static not desired)
    target_link_libraries(NewtonPolygon sfml-graphics sfml-window sfml-system)
endif()

# -------------------- IDE Folders --------------------
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
