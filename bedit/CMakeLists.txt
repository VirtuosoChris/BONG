cmake_minimum_required(VERSION 3.16)

# set the project name
project(Bong)

add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)

# add the executable
add_executable(bedit
dialogboxfunc.cpp
draw.cpp
editor.h
errors.cpp
menufuncs.cpp
resource.h
resource.rc
WinMain.cpp
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Link OpenGL
target_link_libraries(bedit OpenGL::GL OpenGL::GLU winmm)

set_target_properties(bedit PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

set_target_properties(bedit PROPERTIES LINK_FLAGS "/ENTRY:WinMainCRTStartup")