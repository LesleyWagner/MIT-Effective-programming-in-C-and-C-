# CMakeList.txt : CMake project for Problem_1_Floating_Point, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable(Problem_2_Matrix_Multiplication "Problem_2_Matrix_Multiplication.c")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:10000000")
