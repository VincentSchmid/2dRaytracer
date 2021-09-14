cmake_minimum_required(VERSION 3.0.0)
project(2dRayTracer VERSION 0.1.0)

INCLUDE_DIRECTORIES(
    c:/dev/vcpkg/installed/x64-windows/include
    C:/dev/MathX/mathLib
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

LINK_DIRECTORIES(
    C:/dev/vcpkg/installed/x64-windows/lib
    C:/dev/MathX/x64/$(Configuration)
)

find_package(blaze CONFIG REQUIRED)

add_executable(2dRayTracer src/main.cpp)

TARGET_LINK_LIBRARIES(2dRayTracer
    raylib mathLib blaze::blaze
)
