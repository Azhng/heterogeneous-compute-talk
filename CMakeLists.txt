cmake_minimum_required (VERSION 3.1)

project(sh19talk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Handle OpenCL
find_package(OpenCL REQUIRED)

subdirs(src)
