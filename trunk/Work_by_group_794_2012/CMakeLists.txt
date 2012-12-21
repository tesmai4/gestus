cmake_minimum_required(VERSION 2.8)

project(gestus)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/out/)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/out/)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src/)

