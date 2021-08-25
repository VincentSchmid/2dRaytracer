cmake_minimum_required(VERSION 3.0.0)
project(2dRayTracer VERSION 0.1.0)

INCLUDE_DIRECTORIES(
    c:/dev/vcpkg/installed/x64-windows/include
    C:/dev/MathX/mathLib
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

LINK_DIRECTORIES(
    C:/dev/vcpkg/installed/x64-windows/lib
    C:/dev/MathX/x64/$(Configuration)
)

add_executable(2dRayTracer main.cpp)

TARGET_LINK_LIBRARIES(2dRayTracer
    raylib mathLib
)
