cmake_minimum_required(VERSION 3.0.0)
project(RaylibInit VERSION 0.1.0)

INCLUDE_DIRECTORIES(
    c:/dev/vcpkg/installed/x64-windows/include
    C:/dev/MathX/mathLib
)

LINK_DIRECTORIES(
    C:/dev/vcpkg/installed/x64-windows/lib
    C:/dev/MathX/x64/Debug
)

add_executable(RaylibInit main.cpp)

TARGET_LINK_LIBRARIES(RaylibInit
    raylib mathLib
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
