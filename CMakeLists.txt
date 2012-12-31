cmake_minimum_required(VERSION 2.8) 
project(libccoifits)

# Compile with C++11 support.  Disable __STRICT_ANSI__ to support 
# some nice OpenCL shortcuts (i.e. cl_float2's .s0, .s1 syntax).
if("${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ARG1}" MATCHES ".*clang")
    ADD_DEFINITIONS("-stdlib=libc++")
endif("${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ARG1}" MATCHES ".*clang")
ADD_DEFINITIONS("-std=c++0x")

#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE DEBUG)
# Default debug level (mostly status messages, some copy-back numbers):
set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wshadow -D DEBUG")
# For even more verbose debugging output:
#set(CMAKE_CXX_FLAGS_DEBUG "-g -D DEBUG -D DEBUG_VERBOSE")

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# Include and build Google Test framework:
ADD_SUBDIRECTORY (lib/gtest-1.6.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(src)
