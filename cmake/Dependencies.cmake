# Dependencies.cmake

option(USE_CPM "Use CPM to obtain and manage dependedency packages" ON)

if(USE_CPM)
  include("${CMAKE_CURRENT_LIST_DIR}/CPM.cmake")

  CPMAddPackage("gh:fmtlib/fmt#7.1.3")

  if(BUILD_TESTING)
    CPMAddPackage("gh:catchorg/Catch2@3.4.0")
    include("${Catch2_SOURCE_DIR}/extras/Catch.cmake")
  endif()
else()
  find_package(fmt REQUIRED)

  if(BUILD_TESTING)
    find_package(Catch2 3 REQUIRED)
    include(Catch)
  endif()
endif()
