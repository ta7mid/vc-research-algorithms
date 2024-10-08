cmake_minimum_required(VERSION 3.14)
project(VertexCoverResearch LANGUAGES C CXX)

include(cmake/CPM.cmake)
CPMAddPackage("gh:fmtlib/fmt#11.0.2")

add_library(algorithms
  src/algorithms/dfs.cxx
  src/algorithms/dfs.h
  src/algorithms/ilst.cxx
  src/algorithms/ilst.h
)
target_compile_features(algorithms PRIVATE cxx_std_11)

add_library(helpers
  src/helpers/io.cxx
  src/helpers/io.h      # private header
  include/helpers/io.h  # public header
)
target_compile_features(helpers PRIVATE cxx_std_11)
target_include_directories(helpers PUBLIC include)
target_link_libraries(helpers PRIVATE fmt::fmt)

include(CTest)
if(BUILD_TESTING)
  CPMAddPackage("gh:doctest/doctest@2.4.11")
  include("${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake")

  add_executable(dfs_test src/algorithms/dfs.test.cxx)
  target_compile_features(dfs_test PRIVATE cxx_std_11)
  target_compile_definitions(dfs_test PRIVATE TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/data/")
  target_link_libraries(dfs_test PRIVATE doctest::doctest algorithms helpers)

  add_executable(ilst_test src/algorithms/ilst.test.cxx)
  target_compile_features(ilst_test PRIVATE cxx_std_11)
  target_compile_definitions(ilst_test PRIVATE TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/data/")
  target_link_libraries(ilst_test PRIVATE doctest::doctest algorithms helpers)

  doctest_discover_tests(dfs_test)
  doctest_discover_tests(ilst_test)
endif()
