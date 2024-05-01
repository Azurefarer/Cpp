cmake_minimum_required(VERSION 3.10)

project(Physics_Simulation
VERSION 0.1
DESCRIPTION "Physics Simulation project with CMake"
LANGUAGES CXX
)

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
#                               "${CMAKE_CURRENT_SOURCE_DIR}"
# )

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
endif()

include(FetchContent)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_MODULE_PATH )
enable_language(C)

# GLFW library
FetchContent_Declare(
  glfw3
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw3)

# Set global header list from include dir
# Use full path to .h files
set(HEADER_LIST "${PROJECT_BINARY_DIR}/../external/glad/glad.h"
                "${PROJECT_BINARY_DIR}/../external/KHR/khrplatform.h"
                "${PROJECT_BINARY_DIR}/../src/exercises/exercises.h"
                "${PROJECT_BINARY_DIR}/../src/tutorial/tutorial.h"
                "${PROJECT_BINARY_DIR}/../src/shader_class/shader_class.h"
                "${PROJECT_BINARY_DIR}/../external/stb_image/stb_image.h"
                "${PROJECT_BINARY_DIR}/../src/supplemental/supplemental.h"
                "${PROJECT_BINARY_DIR}/../apps/main/main.h"
)

# External Libs
add_library(glad external/glad/glad.c "${HEADER_LIST}")
set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)
target_include_directories(glad PUBLIC "external")

add_library(external_libs external/KHR/KHR.cpp external/stb_image/stb_image.cpp "${HEADER_LIST}")
target_include_directories(external_libs PUBLIC "external")

# src libs
add_library(src_libs apps/main/main.cpp 
                     src/tutorial/tutorial.cpp 
                     src/exercises/exercises.cpp 
                     src/shader_class/shader_class.cpp 
                     src/supplemental/supplemental.cpp 
                     "${HEADER_LIST}"
)
target_include_directories(src_libs PUBLIC
                            "src"
                            "external/glad"
)
# supplemental depends on glad
target_link_libraries(src_libs PRIVATE glad)
target_link_libraries(src_libs PRIVATE glfw3)

add_executable(Physics_Simulation apps/main/main.cpp)
target_include_directories(Physics_Simulation PUBLIC "apps")

# Necessary libraries for project to compile at compile-time
target_link_libraries(Physics_Simulation PRIVATE glad)
target_link_libraries(Physics_Simulation PRIVATE src_libs)
target_link_libraries(Physics_Simulation PRIVATE external_libs)
target_link_libraries(Physics_Simulation PRIVATE glfw3)

# neccessary compile features to compile(basically like the version of the compiler)
target_compile_features(Physics_Simulation PRIVATE cxx_std_17)
