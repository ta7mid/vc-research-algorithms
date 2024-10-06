cmake_minimum_required(VERSION 3.10)
project(VertexCoverResearch LANGUAGES C CXX)

include(CTest)

add_library(algorithms src/algorithms/traversal.cxx)
target_compile_features(algorithms PRIVATE cxx_std_11)
target_include_directories(algorithms PUBLIC include)

if(BUILD_TESTING)
  find_package(doctest REQUIRED)

  add_executable(traversal_test src/algorithms/traversal.test.cxx)
  target_link_libraries(traversal_test PRIVATE algorithms doctest::doctest)
  target_compile_features(traversal_test PRIVATE cxx_std_11)

  add_test(
    NAME algorithms_tests
    COMMAND traversal_test
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/data
  )
endif()
