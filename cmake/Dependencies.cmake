# Dependencies.cmake

option(USE_CPM "Use CPM to obtain and manage dependedency packages" OFF)

if(USE_CPM)
  include("${CMAKE_CURRENT_LIST_DIR}/internal/GetCPM.cmake")

  set(backup_clang_tidy_cmd "${CMAKE_CXX_CLANG_TIDY}")
  set(backup_cppcheck_cmd "${CMAKE_CXX_CPPCHECK}")
  set(backup_iwyu_cmd "${CMAKE_CXX_INCLUDE_WHAT_YOU_USE}")
  unset(CMAKE_CXX_CLANG_TIDY)
  unset(CMAKE_CXX_CPPCHECK)
  unset(CMAKE_CXX_INCLUDE_WHAT_YOU_USE)

  CPMAddPackage("gh:fmtlib/fmt#11.2.0")

  if(BUILD_TESTING)
    CPMAddPackage("gh:catchorg/Catch2@3.8.1")
    include("${Catch2_SOURCE_DIR}/extras/Catch.cmake")
  endif()

  set(CMAKE_CXX_CLANG_TIDY "${backup_clang_tidy_cmd}")
  set(CMAKE_CXX_CPPCHECK "${backup_cppcheck_cmd}")
  set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${backup_iwyu_cmd}")
  unset(backup_clang_tidy_cmd)
  unset(backup_cppcheck_cmd)
  unset(backup_iwyu_cmd)
else()
  find_package(fmt REQUIRED)

  if(BUILD_TESTING)
    find_package(Catch2 3 REQUIRED)
    include(Catch)
  endif()
endif()
