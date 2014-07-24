# Define project settings.
project (Baseline  C) 
cmake_minimum_required (VERSION 2.6)
cmake_policy(SET CMP0042 NEW) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_C_FLAGS  "-g -Wall -O2")

# Build library.
file(GLOB_RECURSE src_files
  "sources/*.h"
  "sources/*.c"
)
add_library(baseline STATIC ${src_files} PREFIX "")

# Build test executable.
file(GLOB_RECURSE test_files
  "tests/*.h"
  "tests/*.c"
)
add_executable(tests ${src_files} ${test_files})