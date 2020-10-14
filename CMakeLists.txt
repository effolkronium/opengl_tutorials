cmake_minimum_required(VERSION 3.14)

project(diplom LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw-3.3.2)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/glm)

SET(ASSIMP_BUILD_TESTS CACHE BOOL OFF)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/assimp-5.0.1)

set_target_properties(glfw PROPERTIES FOLDER external/glfw)
set_target_properties(uninstall PROPERTIES FOLDER external/glfw)

find_package(OpenGL REQUIRED)

add_subdirectory(source)