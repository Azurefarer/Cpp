cmake_minimum_required(VERSION 3.10)

project(hello_world)

add_library(header src/header.cpp "${PROJECT_BINARY_DIR}/../include/header/header.h")
target_include_directories(header PUBLIC "${PROJECT_BINARY_DIR}/../include")

add_executable(hello_world apps/helloworld.cpp)

target_link_libraries(hello_world PRIVATE header)
