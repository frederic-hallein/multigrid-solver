cmake_minimum_required(VERSION 3.10)
project("multigrid-solver")

# Use C++17 (you were seeing C++17 nested-namespace warnings)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find yaml-cpp package
find_package(yaml-cpp REQUIRED)

# --------------------------------------------------
# Source files: recurse into subdirectories under src/
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Remove main.cpp from SRC_FILES for tests
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Main executable
add_executable(main ${CMAKE_SOURCE_DIR}/src/main.cpp ${SRC_FILES})

# Include directories for headers in subfolders
target_include_directories(main PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/common
    ${CMAKE_SOURCE_DIR}/src/multigrid
    ${CMAKE_SOURCE_DIR}/src/multigrid/cartesian_1d
)

# --------------------------------------------------
# Google Test setup (as submodule in external/)
add_subdirectory(external/googletest)

# --------------------------------------------------
# Test files (all .cpp files in tests/)
file(GLOB TEST_FILES ${CMAKE_SOURCE_DIR}/tests/*.cpp)

# Link yaml-cpp to main executable
target_link_libraries(main yaml-cpp)

foreach(test_src ${TEST_FILES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src} ${SRC_FILES})

    target_include_directories(${test_name} PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/common
        ${CMAKE_SOURCE_DIR}/src/multigrid
        ${CMAKE_SOURCE_DIR}/src/multigrid/cartesian_1d
    )

    target_link_libraries(${test_name} gtest gtest_main pthread)
    set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

enable_testing()