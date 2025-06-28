# Linters.cmake

# these tools use compile_commands.json
if(NOT (PROJECT_IS_TOP_LEVEL AND CMAKE_EXPORT_COMPILE_COMMANDS))
  return()
endif()

option(ENABLE_CMD_TARGET_RUN_CLANG_TIDY "Enable adding a custom target for running Clang-Tidy" OFF)
if(ENABLE_CMD_TARGET_RUN_CLANG_TIDY)
  if(DEFINED ENV{RUN_CLANG_TIDY_EXECUTABLE})
    set(RUN_CLANG_TIDY_EXECUTABLE "$ENV{RUN_CLANG_TIDY_EXECUTABLE}")
  else()
    find_program(RUN_CLANG_TIDY_EXECUTABLE "run-clang-tidy" REQUIRED)
  endif()

  if(DEFINED ENV{CLANG_TIDY_EXECUTABLE})
    set(CLANG_TIDY_EXECUTABLE "$ENV{CLANG_TIDY_EXECUTABLE}")
  else()
    find_program(CLANG_TIDY_EXECUTABLE "clang-tidy" REQUIRED)
  endif()

  set(cmd
    "${RUN_CLANG_TIDY_EXECUTABLE}"
    "-clang-tidy-binary=${CLANG_TIDY_EXECUTABLE}"
    "-p=${CMAKE_BINARY_DIR}"
    "-config-file=${CMAKE_SOURCE_DIR}/.clang-tidy"
    "-export-fixes=${CMAKE_SOURCE_DIR}/out/lint/clang_tidy_fixes/"
    "$ENV{CLANG_TIDY_EXTRA_ARGS}"
  )

  add_custom_target(run_clang_tidy COMMAND ${cmd})
  add_custom_target(run_clang_tidy_fix COMMAND ${cmd} "-fix")
endif()

option(ENABLE_CMD_TARGET_RUN_CPPCHECK "Enable adding a custom target for running Cppcheck" OFF)
if(ENABLE_CMD_TARGET_RUN_CPPCHECK)
  if(DEFINED ENV{CPPCHECK_EXECUTABLE})
    set(CPPCHECK_EXECUTABLE "$ENV{CPPCHECK_EXECUTABLE}")
  else()
    find_program(CPPCHECK_EXECUTABLE "cppcheck" REQUIRED)
  endif()

  add_custom_target(run_cppcheck
    COMMAND
      "${CPPCHECK_EXECUTABLE}"
      "--project=${CMAKE_BINARY_DIR}/compile_commands.json"
      "--cppcheck-build-dir=${CMAKE_SOURCE_DIR}/out/lint/cppcheck_cache/"
      "--language=c++"
      "--enable=warning,style,performance,portability"
      "--check-level=exhaustive"
      "$ENV{CPPCHECK_EXTRA_ARGS}"
  )
endif()
