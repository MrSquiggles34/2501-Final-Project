cmake_minimum_required(VERSION 3.18)

# Project name
set(PROJ_NAME "2501FinalProject")
project(${PROJ_NAME})

# Make sure the compiler knows where to find the header files
add_compile_options(-I ${CMAKE_CURRENT_SOURCE_DIR}/header)

# Add files
add_executable(${PROJ_NAME} "")
add_subdirectory(source)
add_subdirectory(header)
#add_subdirectory(shader)

# Add path name to configuration file
configure_file(path_config.h.in path_config.h)

# path_config.h
target_include_directories(${PROJ_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# Require OpenGL library
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJ_NAME} ${OPENGL_gl_LIBRARY})

# Other libraries needed
set(LIBRARY_PATH $ENV{COMP2501_LIBRARY_PATH} CACHE PATH "Folder with GLEW, GLFW, GLM, and SOIL libraries")
include_directories(${LIBRARY_PATH}/include)
if(NOT WIN32)
	find_library(GLEW_LIBRARY GLEW)
	find_library(GLFW_LIBRARY glfw)
	find_library(SOIL_LIBRARY SOIL)
elseif(WIN32)
	find_library(GLEW_LIBRARY glew32s HINTS ${LIBRARY_PATH}/lib)
	find_library(GLFW_LIBRARY glfw3 HINTS ${LIBRARY_PATH}/lib)
	find_library(SOIL_LIBRARY SOIL HINTS ${LIBRARY_PATH}/lib)
endif(NOT WIN32)
target_link_libraries(${PROJ_NAME} ${GLEW_LIBRARY})
target_link_libraries(${PROJ_NAME} ${GLFW_LIBRARY})
target_link_libraries(${PROJ_NAME} ${SOIL_LIBRARY})

# The rules here are specific to Windows Systems
if(WIN32)
	# Avoid ZERO_CHECK target in Visual Studio
	set(CMAKE_SUPPRESS_REGENERATION TRUE)
	
	# This will use the proper libraries in debug mode in Visual Studio
	set_target_properties(${PROJ_NAME} PROPERTIES DEBUG_POSTFIX _d)
	
	# Set the default project in VS
	set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJ_NAME})
endif(WIN32)
