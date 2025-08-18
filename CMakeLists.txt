cmake_minimum_required(VERSION 3.10)
project(NewtonPolygonizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- SFML paths (static build) ---
set(SFML_ROOT "C:/Users/dongh/Desktop/Working_with_Data_CMT_2025/newton-polygon/SFML")
set(SFML_DIR "C:/Users/dongh/Desktop/Working_with_Data_CMT_2025/newton-polygon/SFML/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
include_directories(${SFML_ROOT}/include)
link_directories(${SFML_ROOT}/lib)

# --- Your single file ---
add_executable(NewtonPolygonizer newton_polygonizer.cpp)

# --- Force static SFML ---
target_compile_definitions(NewtonPolygonizer PRIVATE SFML_STATIC)
target_link_libraries(NewtonPolygonizer
    sfml-graphics-s
    sfml-window-s
    sfml-system-s
    opengl32
    freetype
    winmm
    gdi32
    ws2_32
)
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
