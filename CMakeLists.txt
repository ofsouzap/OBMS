# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# OBMS - Ofsouzap dataBase Management System
project ("OBMS")

# Include sub-projects.
add_subdirectory ("libOBMS")
add_subdirectory ("examples")
