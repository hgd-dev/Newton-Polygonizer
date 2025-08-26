cmake_minimum_required(VERSION 3.15)
project(NewtonPolygonizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(NewtonPolygonizer newton_polygonizer_nowindow.cpp)
add_executable(PolyLongDiv polynomial_long_division.cpp)

