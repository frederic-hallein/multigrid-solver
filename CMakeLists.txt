cmake_minimum_required(VERSION 3.28.3)
project("multigrid-solver")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(yaml-cpp REQUIRED)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Remove main.cpp from SRC_FILES for tests
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_executable(main ${CMAKE_SOURCE_DIR}/src/main.cpp ${SRC_FILES})

target_include_directories(main PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/common
    ${CMAKE_SOURCE_DIR}/src/multigrid
    ${CMAKE_SOURCE_DIR}/src/multigrid/cartesian_1d
)

add_subdirectory(external/googletest)

file(GLOB TEST_FILES ${CMAKE_SOURCE_DIR}/tests/*.cpp)

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
