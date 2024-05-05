cmake_minimum_required(VERSION 3.10)

project(hello_gl
VERSION 0.1
DESCRIPTION "Hello World with OpenGL"
LANGUAGES CXX
)

enable_language(C)

include(FetchContent)
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

set(HEADER_LIST 
    "${PROJECT_SOURCE_DIR}/src/external_libs/glad/glad.h"
    "${PROJECT_SOURCE_DIR}/src/external_libs/KHR/khrplatform.h"
    "${PROJECT_SOURCE_DIR}/src/external_libs/stb_image/stb_image.h"
    "${PROJECT_SOURCE_DIR}/src/apps/main/main.h"
)

add_library(glad "${PROJECT_SOURCE_DIR}/src/external_libs/glad/glad.c" "${HEADER_LIST}")
set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)
# glad needs to see KHR Platform header (Khronos Group thing)
target_include_directories(glad PUBLIC "src/external_libs")

add_library(external_libs 
    "${PROJECT_SOURCE_DIR}/src/external_libs/KHR/KHR.cpp"
    "${PROJECT_SOURCE_DIR}/src/external_libs/stb_image/stb_image.cpp"
    "${HEADER_LIST}"
)
target_include_directories(external_libs PUBLIC "src/external_libs")

add_library(src_libs
    "${PROJECT_SOURCE_DIR}/src/apps/main/main.cpp"
    "${HEADER_LIST}"
)
target_include_directories(src_libs PUBLIC
    "src"
    "src/external_libs/glad"
    "${glfw3_SOURCE_DIR}/include"
)
target_link_libraries(src_libs PRIVATE 
    glad
    "${PROJECT_SOURCE_DIR}/build/_deps/glfw3-build/src/libglfw3.a"
)

add_executable(hello_gl "${PROJECT_SOURCE_DIR}/src/apps/main/main.cpp")
# Necessary libraries for project to compile at compile-time
target_link_libraries(hello_gl PRIVATE 
    glad
    src_libs
    external_libs
    "${PROJECT_SOURCE_DIR}/build/_deps/glfw3-build/src/libglfw3.a"
    opengl32  # look for OpenGL32.lib in default ENV VAR PATH
)
