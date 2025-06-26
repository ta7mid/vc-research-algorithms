cmake_minimum_required(VERSION 3.24)
project(VertexCoverResearchAlgorithms LANGUAGES CXX)

include(CTest)
include("cmake/Dependencies.cmake")
include("cmake/CompilerOptions.cmake")
include("cmake/Sanitizers.cmake")

set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)


#
# Library targets
#

add_library(common INTERFACE)
target_sources(common
  INTERFACE
    FILE_SET HEADERS
    BASE_DIRS "include/"
    FILES "common/constants.h"
)
target_compile_features(common INTERFACE cxx_constexpr)

add_library(algorithms INTERFACE)
target_sources(algorithms
  INTERFACE
    FILE_SET HEADERS
    BASE_DIRS "include/"
    FILES
      "algorithms/connectivity.h"
      "algorithms/dfs.h"
      "algorithms/ilst.h"
      "algorithms/orderings.h"
      "algorithms/vertex_cover.h"
  INTERFACE
    "src/algorithms/connectivity.cxx"
    "src/algorithms/dfs.cxx"
    "src/algorithms/ilst.cxx"
    "src/algorithms/orderings.cxx"
    "src/algorithms/vertex_cover.cxx"
    "src/algorithms/vertex_cover.h"
)
target_compile_features(algorithms INTERFACE cxx_std_14)

add_library(io_helpers INTERFACE)
target_sources(io_helpers
  INTERFACE
    FILE_SET HEADERS
    BASE_DIRS "include/"
    FILES "io_helpers/io_helpers.h"
  INTERFACE
    "src/io_helpers/io_helpers.cxx"
    "src/io_helpers/io_helpers.h"
)
target_compile_features(io_helpers INTERFACE cxx_std_11)
target_link_libraries(io_helpers INTERFACE fmt::fmt-header-only common)

add_library(graph_helpers INTERFACE)
target_sources(graph_helpers
  INTERFACE
    FILE_SET HEADERS
    BASE_DIRS "include/"
    FILES "graph_helpers/graph_helpers.h"
  INTERFACE "src/graph_helpers/graph_helpers.cxx"
)
target_compile_features(graph_helpers INTERFACE cxx_std_17)


#
# Executable targets
#

add_executable(cvc "src/cmd/cvc/main.cxx")
target_compile_features(cvc PRIVATE cxx_std_11)
target_link_libraries(cvc PRIVATE fmt::fmt-header-only algorithms graph_helpers io_helpers)

add_executable(vc "src/cmd/vc/main.cxx")
target_compile_features(vc PRIVATE cxx_std_11)
target_link_libraries(vc PRIVATE fmt::fmt-header-only algorithms graph_helpers io_helpers)

add_executable(local_ratio_vc "src/cmd/local_ratio_vc/main.cxx")
target_compile_features(local_ratio_vc PRIVATE cxx_std_11)
target_link_libraries(local_ratio_vc PRIVATE fmt::fmt-header-only algorithms io_helpers)


#
# Test targets
#

if(NOT BUILD_TESTING)
  return()
endif()

add_executable(connectivity_test "src/algorithms/connectivity.test.cxx")
target_compile_features(connectivity_test PRIVATE cxx_std_11)
target_compile_definitions(connectivity_test PRIVATE TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/data/")
target_link_libraries(connectivity_test
  PRIVATE Catch2::Catch2WithMain algorithms io_helpers
)

add_executable(dfs_test "src/algorithms/dfs.test.cxx")
target_compile_features(dfs_test PRIVATE cxx_std_11)
target_compile_definitions(dfs_test PRIVATE TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/data/")
target_link_libraries(dfs_test
  PRIVATE Catch2::Catch2WithMain algorithms io_helpers
)

add_executable(ilst_test "src/algorithms/ilst.test.cxx")
target_compile_features(ilst_test PRIVATE cxx_std_17)
target_compile_definitions(ilst_test PRIVATE TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/data/")
target_link_libraries(ilst_test
  PRIVATE Catch2::Catch2WithMain algorithms graph_helpers io_helpers
)

add_executable(vertex_cover_test "src/algorithms/vertex_cover.test.cxx")
target_compile_features(vertex_cover_test PRIVATE cxx_std_11)
target_compile_definitions(vertex_cover_test PRIVATE TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/data/")
target_link_libraries(vertex_cover_test
  PRIVATE Catch2::Catch2WithMain algorithms io_helpers
)

catch_discover_tests(connectivity_test)
catch_discover_tests(dfs_test)
catch_discover_tests(ilst_test)
catch_discover_tests(vertex_cover_test)
