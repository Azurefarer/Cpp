cmake_minimum_required(VERSION 3.10)

project(Physics_Simulation
VERSION 0.1
DESCRIPTION "Physics Simulation project with CMake"
LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_MODULE_PATH )
enable_language(C)

include(FetchContent)
# GLFW library
FetchContent_Declare(
  glfw3
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
  SOURCE_DIR "${PROJECT_SOURCE_DIR}/../opencv"
  )
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw3)

# Set global header list from include dir
# Use full path to .h files
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/src/external_libs/glad/glad.h"
                "${PROJECT_SOURCE_DIR}/src/external_libs/KHR/khrplatform.h"
                "${PROJECT_SOURCE_DIR}/src/exercises/exercises.h"
                "${PROJECT_SOURCE_DIR}/src/tutorial/tutorial.h"
                "${PROJECT_SOURCE_DIR}/src/shader_class/shader_class.h"
                "${PROJECT_SOURCE_DIR}/src/external_libs/stb_image/stb_image.h"
                "${PROJECT_SOURCE_DIR}/src/supplemental/supplemental.h"
                "${PROJECT_SOURCE_DIR}/src/apps/main/main.h"
)

# External Libs
add_library(glad "${PROJECT_SOURCE_DIR}/src/external_libs/glad/glad.c" "${HEADER_LIST}")
set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)
target_include_directories(glad PUBLIC "src/external_libs")

add_library(external_libs ${PROJECT_SOURCE_DIR}/src/external_libs/KHR/KHR.cpp
                          ${PROJECT_SOURCE_DIR}/src/external_libs/stb_image/stb_image.cpp
                          "${HEADER_LIST}"
)
target_include_directories(external_libs PUBLIC "src/external_libs")

# src libs
add_library(src_libs ${PROJECT_SOURCE_DIR}/src/apps/main/main.cpp 
                     ${PROJECT_SOURCE_DIR}/src/tutorial/tutorial.cpp 
                     ${PROJECT_SOURCE_DIR}/src/exercises/exercises.cpp 
                     ${PROJECT_SOURCE_DIR}/src/shader_class/shader_class.cpp 
                     ${PROJECT_SOURCE_DIR}/src/supplemental/supplemental.cpp 
                     "${HEADER_LIST}"
)
target_include_directories(src_libs PUBLIC
                            "src"
                            "src/external_libs/glad"
                            "${glfw3_SOURCE_DIR}/include"
)
# supplemental depends on glad
target_link_libraries(src_libs PRIVATE glad)
target_link_libraries(src_libs PRIVATE "${PROJECT_SOURCE_DIR}/build/_deps/glfw3-build/src/libglfw3.a")

add_executable(Physics_Simulation ${PROJECT_SOURCE_DIR}/src/apps/main/main.cpp)
target_include_directories(Physics_Simulation PUBLIC "${glfw3_SOURCE_DIR}/include")

# Necessary libraries for project to compile at compile-time
target_link_libraries(Physics_Simulation PRIVATE glad)
target_link_libraries(Physics_Simulation PRIVATE src_libs)
target_link_libraries(Physics_Simulation PRIVATE external_libs)
target_link_libraries(Physics_Simulation PRIVATE "${PROJECT_SOURCE_DIR}/build/_deps/glfw3-build/src/libglfw3.a")

# neccessary compile features to compile(basically like the version of the compiler)
target_compile_features(Physics_Simulation PRIVATE cxx_std_17)
