# Adds options for enabling AddressSanitizer, LeakSanitizer, MemorySanitizer, ThreadSanitizer, and
# UndefinedBehaviorSanitizer
#
#
# The code in this file is adapted from
#
#     Scott, Craig. “Appendix B: Sanitizers Example”. _Professional CMake: A Practical Guide_. 21st ed., 20 May 2025.
#         _Crascit_, https://crascit.com/professional-cmake/. EPUB.
#
# The copyright message from the book states the following:
#
#     Permission is given to use any of the code samples in this work without restriction. Attribution is not required.
#

option(ENABLE_ASAN "Enable AddressSanitizer" NO)

if(MSVC)
  if(ENABLE_ASAN)
    string(REPLACE "/RTC1" ""
      CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}"
    )
    string(REPLACE "/RTC1" ""
      CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}"
    )
    add_compile_options(
      /fsanitize=address
      /fsanitize-address-use-after-return
    )
  endif()
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  option(ENABLE_LSAN "Enable LeakSanitizer" NO)
  option(ENABLE_TSAN "Enable ThreadSanitizer" NO)
  if(NOT APPLE)
    option(ENABLE_MSAN "Enable MemorySanitizer" NO)
  endif()
  option(ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer" $<NOT:$<CONFIG:Release>>)

  if((ENABLE_ASAN AND (ENABLE_TSAN OR ENABLE_MSAN)) OR
     (ENABLE_LSAN AND (ENABLE_TSAN OR ENABLE_MSAN)) OR
     (ENABLE_TSAN AND ENABLE_MSAN))
    message(FATAL_ERROR
      "Invalid sanitizer combination:\n"
      "  ENABLE_ASAN:  ${ENABLE_ASAN}\n"
      "  ENABLE_LSAN:  ${ENABLE_LSAN}\n"
      "  ENABLE_TSAN:  ${ENABLE_TSAN}\n"
      "  ENABLE_MSAN:  ${ENABLE_MSAN}"
    )
  endif()

  set(ubsan_flag "-fsanitize=undefined")
  if(CMAKE_C_COMPILER_ID STREQUAL GNU)
    # https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html#index-fsanitize_003dundefined
    string(APPEND ubsan_flag ",bounds-strict")
  else()
    # https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html#available-checks
    string(APPEND ubsan_flag ",implicit-conversion,bounds,nullability")
  endif()

  add_compile_options(
    -fno-omit-frame-pointer
    $<$<BOOL:${ENABLE_ASAN}>:-fsanitize=address>
    $<$<BOOL:${ENABLE_LSAN}>:-fsanitize=leak>
    $<$<BOOL:${ENABLE_MSAN}>:-fsanitize=memory>
    $<$<BOOL:${ENABLE_TSAN}>:-fsanitize=thread>
    $<$<BOOL:${ENABLE_UBSAN}>:${ubsan_flag}>
  )
  add_link_options(
    $<$<BOOL:${ENABLE_ASAN}>:-fsanitize=address>
    $<$<BOOL:${ENABLE_LSAN}>:-fsanitize=leak>
    $<$<BOOL:${ENABLE_MSAN}>:-fsanitize=memory>
    $<$<BOOL:${ENABLE_TSAN}>:-fsanitize=thread>
    $<$<BOOL:${ENABLE_UBSAN}>:${ubsan_flag}>
  )
endif()
