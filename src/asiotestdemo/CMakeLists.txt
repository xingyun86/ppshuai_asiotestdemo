﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("asiotestdemo")

# Include sub-projects.
add_subdirectory ("vendor/libressl-3.1.1")
add_subdirectory ("asiotestdemo")
add_subdirectory ("coroutinetestdemo")
