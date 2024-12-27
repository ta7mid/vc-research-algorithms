cmake_minimum_required(VERSION 3.14)
project(VertexCoverResearch LANGUAGES C CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/CPM.cmake)
CPMAddPackage("gh:fmtlib/fmt#11.0.2")

add_library(common INTERFACE)
target_sources(common INTERFACE include/common/constants.h)
target_compile_features(common INTERFACE cxx_constexpr)
target_include_directories(common INTERFACE include)

add_library(algorithms
  src/algorithms/connectivity.cxx
  include/algorithms/connectivity.h

  src/algorithms/dfs.cxx
  include/algorithms/dfs.h

  src/algorithms/ilst.cxx
  include/algorithms/ilst.h

  src/algorithms/orderings.cxx
  include/algorithms/orderings.h

  src/algorithms/vertex_cover.cxx
  src/algorithms/vertex_cover.h
  include/algorithms/vertex_cover.h
)
target_compile_features(algorithms PRIVATE cxx_std_11)
target_include_directories(algorithms PUBLIC include)
target_link_libraries(algorithms PUBLIC common)

add_library(io_helpers
  src/io_helpers/io_helpers.cxx
  src/io_helpers/io_helpers.h      # private header
  include/io_helpers/io_helpers.h  # public header
)
target_compile_features(io_helpers PRIVATE cxx_std_11)
target_include_directories(io_helpers PUBLIC include)
target_link_libraries(io_helpers PRIVATE fmt::fmt common)

add_library(graph_helpers
  src/graph_helpers/graph_helpers.cxx
  include/graph_helpers/graph_helpers.h
)
target_compile_features(graph_helpers PRIVATE cxx_std_11)
target_include_directories(graph_helpers PUBLIC include)

add_executable(cvc src/cmd/cvc/main.cxx)
target_compile_features(cvc PRIVATE cxx_std_11)
target_link_libraries(cvc PRIVATE fmt::fmt algorithms common graph_helpers io_helpers)

add_executable(vc src/cmd/vc/main.cxx)
target_compile_features(vc PRIVATE cxx_std_11)
target_link_libraries(vc PRIVATE fmt::fmt algorithms common graph_helpers io_helpers)

add_executable(local_ratio_vc src/cmd/local_ratio_vc/main.cxx)
target_compile_features(local_ratio_vc PRIVATE cxx_std_11)
target_link_libraries(local_ratio_vc PRIVATE fmt::fmt io_helpers)

include(CTest)
if(BUILD_TESTING)
  CPMAddPackage("gh:doctest/doctest@2.4.11")
  include("${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake")

  add_executable(connectivity_test src/algorithms/connectivity.test.cxx)
  target_compile_features(connectivity_test PRIVATE cxx_std_11)
  target_compile_definitions(connectivity_test PRIVATE TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/data/")
  target_link_libraries(connectivity_test
    PRIVATE doctest::doctest algorithms io_helpers
  )

  add_executable(dfs_test src/algorithms/dfs.test.cxx)
  target_compile_features(dfs_test PRIVATE cxx_std_11)
  target_compile_definitions(dfs_test PRIVATE TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/data/")
  target_link_libraries(dfs_test
    PRIVATE doctest::doctest algorithms io_helpers
  )

  add_executable(ilst_test src/algorithms/ilst.test.cxx)
  target_compile_features(ilst_test PRIVATE cxx_std_11)
  target_compile_definitions(ilst_test PRIVATE TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/data/")
  target_link_libraries(ilst_test
    PRIVATE doctest::doctest algorithms graph_helpers io_helpers
  )

  add_executable(vertex_cover_test src/algorithms/vertex_cover.test.cxx)
  target_compile_features(vertex_cover_test PRIVATE cxx_std_11)
  target_compile_definitions(vertex_cover_test PRIVATE TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/data/")
  target_link_libraries(vertex_cover_test
    PRIVATE doctest::doctest algorithms common io_helpers
  )

  doctest_discover_tests(connectivity_test)
  doctest_discover_tests(dfs_test)
  doctest_discover_tests(ilst_test)
  doctest_discover_tests(vertex_cover_test)
endif()
