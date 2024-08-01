cmake_minimum_required(VERSION 3.16)

# set the project name
project(Bong)

add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)

# add the executable
add_executable(BongGame
ai.cpp
bong.h
collision.cpp
Draw.cpp
file.cpp
game.cpp
resource.h
WinMain.cpp
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Link OpenGL
target_link_libraries(BongGame OpenGL::GL OpenGL::GLU winmm)

set_target_properties(BongGame PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

set_target_properties(BongGame PROPERTIES LINK_FLAGS "/ENTRY:WinMainCRTStartup")

target_include_directories(BongGame PUBLIC ../Common)