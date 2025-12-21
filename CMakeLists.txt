# Minimum required CMake version and project name
cmake_minimum_required(VERSION 3.10)
project("multigrid-solver")

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# --------------------------------------------------
# Source files (all .cpp files in src/)
file(GLOB SRC_FILES src/*.cpp)

# Remove main.cpp from SRC_FILES for tests
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Main executable (includes main.cpp)
add_executable(main src/main.cpp ${SRC_FILES})

# --------------------------------------------------
# Google Test setup (as submodule in external/)
add_subdirectory(external/googletest)

# --------------------------------------------------
# Test files (all .cpp files in tests/)
file(GLOB TEST_FILES tests/*.cpp)

# Test executable (does NOT include main.cpp)
add_executable(test_solver ${TEST_FILES} ${SRC_FILES})
target_include_directories(test_solver PRIVATE src)
target_link_libraries(test_solver gtest gtest_main pthread)

# Place test executable in build/test/
set_target_properties(test_solver PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)

# --------------------------------------------------
# Enable CTest and register the test executable
enable_testing()
add_test(NAME test_solver COMMAND test_solver)