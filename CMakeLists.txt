cmake_minimum_required(VERSION 3.10)
project("multigrid-solver")

set(CMAKE_CXX_STANDARD 11)

add_executable(main src/main.cpp src/solver.cpp)