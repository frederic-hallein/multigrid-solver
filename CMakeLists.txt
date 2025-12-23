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

# For each test file, create a separate executable and register with CTest
foreach(test_src ${TEST_FILES})
    # Get the filename without directory or extension
    get_filename_component(test_name ${test_src} NAME_WE)
    set(test_exe ${test_name})

    add_executable(${test_exe} ${test_src} ${SRC_FILES})
    target_include_directories(${test_exe} PRIVATE src)
    target_link_libraries(${test_exe} gtest gtest_main pthread)
    set_target_properties(${test_exe} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)

    add_test(NAME ${test_exe} COMMAND ${test_exe})
endforeach()

# --------------------------------------------------
# Enable CTest
enable_testing()