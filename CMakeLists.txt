cmake_minimum_required(VERSION 3.17)

project(ARCADE)

set(CMAKE_CXX_STANDARD 20)
set(CXXFLAGS "-g3 -fno-gnu-unique")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_subdirectory(lib)
add_subdirectory(src)
