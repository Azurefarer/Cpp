cmake_minimum_required(VERSION 3.10)

project(hello_world)

set(CMAKE_CXX_STANDARD 17)

add_library(header 
    ${PROJECT_SOURCE_DIR}/src/header/header.cpp
    ${PROJECT_SOURCE_DIR}/src/header/header.h)

target_include_directories(header PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_executable(hello_world
    ${PROJECT_SOURCE_DIR}/src/apps/helloworld.cpp)
target_link_libraries(hello_world PRIVATE header)
