# CompilerOptions.cmake


#
# Warngings
#
# Curated mainly from the list at
# https://github.com/cpp-best-practices/cppbestpractices/blob/master/02-Use_the_Tools_Available.md#compilers
#

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  add_compile_options(
    "-pedantic-errors"
    "-Weverything"
    "-Wno-c++98-compat"
    "-Wno-missing-prototypes"
  )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(
    "-pedantic-errors" # error if non-standard C++ is used
    "-Wall"
    "-Wextra" # reasonable and standard
    "-Wnon-virtual-dtor" # warn the user if a class with virtual functions has a non-virtual destructor (helps catch hard to track down memory errors)
    "-Wunused" # warn on anything being unused
    "-Wconversion" # warn on type conversions that may lose data
    "-Wsign-conversion" # warn on sign conversions
    "-Wcast-align" # warn for potential performance problem casts
    "-Wimplicit-fallthrough" # warn on statements that fallthrough without an explicit annotation
    "-Wmisleading-indentation" # warn if indentation implies blocks where blocks do not exist
    "-Wnull-dereference" # warn if a null dereference is detected
    "-Wold-style-cast" # warn about C-style casts
    "-Woverloaded-virtual" # warn if you overload (not override) a virtual function
    "-Wshadow" # warn the user if a variable declaration shadows one from a parent context
    "-Wduplicated-cond" # warn if if / else chain has duplicated conditions
    "-Wduplicated-branches" # warn if if / else branches have duplicated code
    "-Wlogical-op" # warn about logical operations being used where bitwise were probably wanted
    "-Wuseless-cast" # warn if you perform a cast to the same type
    "-Wsuggest-override" # warn if an overridden member function is not marked 'override' or 'final'
  )
elseif(MSVC)
  add_compile_options(
    "/W4" # Baseline reasonable warnings
    "/w14242" # 'identifier': conversion from 'type1' to 'type2', possible loss of data
    "/w14254" # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
    "/w14263" # 'function': member function does not override any base class virtual member function
    "/w14265" # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not be destructed correctly
    "/w14287" # 'operator': unsigned/negative constant mismatch
    "/we4289" # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside the for-loop scope
    "/w14296" # 'operator': expression is always 'boolean_value'
    "/w14311" # 'variable': pointer truncation from 'type1' to 'type2'
    "/w14545" # expression before comma evaluates to a function which is missing an argument list
    "/w14546" # function call before comma missing argument list
    "/w14547" # 'operator': operator before comma has no effect; expected operator with side-effect
    "/w14549" # 'operator': operator before comma has no effect; did you intend 'operator'?
    "/w14555" # expression has no effect; expected expression with side- effect
    "/w14619" # pragma warning: there is no warning number 'number'
    "/w14640" # Enable warning on thread un-safe static member initialization
    "/w14826" # Conversion from 'type1' to 'type2' is sign-extended. This may cause unexpected runtime behavior.
    "/w14905" # wide string literal cast to 'LPSTR'
    "/w14906" # string literal cast to 'LPWSTR'
    "/w14928" # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
    "/permissive-" # standards conformance mode for MSVC compiler.
  )
endif()


#
# Implementation-specific debug mode
#
# Source: https://stackoverflow.com/a/78242553
#

include(CheckCXXSymbolExists)

if("cxx_std_20" IN_LIST CMAKE_CXX_COMPILE_FEATURES) # C++20 is supported
  set(header "version")
else()
  set(header "ciso646")
endif()

# standard library impl == GNU libstdc++?
check_cxx_symbol_exists("__GLIBCXX__" "${header}" using_libstdcxx)

if(using_libstdcxx)
  add_compile_definitions(
    $<$<CONFIG:Debug>:_GLIBCXX_DEBUG>
    $<$<CONFIG:RelWithDebInfo>:_GLIBCXX_ASSERTIONS>
  )
  return()  # skip the check for LLVM libc++
endif()

# standard library impl == LLVM libc++?
check_cxx_symbol_exists("_LIBCPP_VERSION" "${header}" using_libcxx)

if(using_libcxx)
  add_compile_definitions($<$<CONFIG:Debug>:_LIBCPP_DEBUG>)
endif()
