# Define project settings.
cmake_minimum_required (VERSION 2.6) 
project (Baseline  C) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_C_FLAGS  "-g -Wall -O2")

# Build library.
file(GLOB_RECURSE src_files
  "src/*.h"
  "src/*.c"
)
add_library(baseline_static STATIC ${src_files})
add_library(baseline SHARED ${src_files})

# Build test executable.
file(GLOB_RECURSE test_files
  "test/*.h"
  "test/*.c"
)
add_executable(test ${src_files} ${test_files})