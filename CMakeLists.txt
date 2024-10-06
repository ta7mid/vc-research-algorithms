cmake_minimum_required(VERSION 3.10)
project(VertexCoverResearch LANGUAGES C CXX)

option(ENABLE_TESTS "Enable tests" ON)

# add_library(graph src/graph/graph.cxx)
# target_include_directories(graph PUBLIC include)

if(ENABLE_TESTS)
  find_package(doctest REQUIRED)

  # add_executable(graph_test src/graph/graph.test.cxx)
  # target_link_libraries(graph_test PRIVATE graph doctest::doctest)
endif()
