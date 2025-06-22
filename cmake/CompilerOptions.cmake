#
# 1. Compiler Warngings
#
# Adapted from the curated list at
# https://github.com/cpp-best-practices/cppbestpractices/blob/master/02-Use_the_Tools_Available.md#compilers
#

if(MSVC)
  set(options
    /W4 # Baseline reasonable warnings
    /w14242 # 'identifier': conversion from 'type1' to 'type2', possible loss of data
    /w14254 # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
    /w14263 # 'function': member function does not override any base class virtual member function
    /w14265 # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not be destructed correctly
    /w14287 # 'operator': unsigned/negative constant mismatch
    /we4289 # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside the for-loop scope
    /w14296 # 'operator': expression is always 'boolean_value'
    /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
    /w14545 # expression before comma evaluates to a function which is missing an argument list
    /w14546 # function call before comma missing argument list
    /w14547 # 'operator': operator before comma has no effect; expected operator with side-effect
    /w14549 # 'operator': operator before comma has no effect; did you intend 'operator'?
    /w14555 # expression has no effect; expected expression with side- effect
    /w14619 # pragma warning: there is no warning number 'number'
    /w14640 # Enable warning on thread un-safe static member initialization
    /w14826 # Conversion from 'type1' to 'type2' is sign-extended. This may cause unexpected runtime behavior.
    /w14905 # wide string literal cast to 'LPSTR'
    /w14906 # string literal cast to 'LPWSTR'
    /w14928 # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
    /permissive- # standards conformance mode for MSVC compiler.
  )
else()
  # options common to both Clang and GCC
  set(options
    -pedantic-errors # error if non-standard C++ is used
    -Wall
    -Wextra # reasonable and standard
    -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor (helps catch hard to track down memory errors)
    -Wunused # warn on anything being unused
    -Wconversion # warn on type conversions that may lose data
    -Wsign-conversion # warn on sign conversions
    -Wcast-align # warn for potential performance problem casts
    -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
    -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
    -Wnull-dereference # warn if a null dereference is detected
    -Wold-style-cast # warn about C-style casts
    -Woverloaded-virtual # warn if you overload (not override) a virtual function
    -Wshadow # warn the user if a variable declaration shadows one from a parent context
  )
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC-only options
    list(APPEND options
      -Wduplicated-cond # warn if if / else chain has duplicated conditions
      -Wduplicated-branches # warn if if / else branches have duplicated code
      -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
      -Wuseless-cast # warn if you perform a cast to the same type
      -Wsuggest-override # warn if an overridden member function is not marked 'override' or 'final'
    )
  endif()
endif()
add_compile_options("${options}")


#
# 2. Definitions for debug mode
#

include(CheckCXXSymbolExists)

function(identify_stdlib_using_cpp_macro outvar symbol)
  if(cxx_std_20 IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    set(header "version")
  else()
    set(header "ciso646")
  endif()
  check_cxx_symbol_exists("${symbol}" "${header}" outvar)
endfunction()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  identify_stdlib_using_cpp_macro(libcxx "_LIBCPP_VERSION")
  if(libcxx) # using LLVM libc++
    add_compile_definitions(_LIBCPP_DEBUG=1)
  else()
    identify_stdlib_using_cpp_macro(libstdcxx "__GLIBCXX__")
    if(libstdcxx) # using GNU libstdc++
      add_compile_definitions(_GLIBCXX_DEBUG=1)
    endif()
  endif()
elseif(CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
  identify_stdlib_using_cpp_macro(libstdcxx "__GLIBCXX__")
  if(libstdcxx)
    add_compile_definitions(_GLIBCXX_ASSERTIONS=1)
  endif()
endif()
