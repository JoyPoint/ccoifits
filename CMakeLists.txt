cmake_minimum_required(VERSION 2.8) 
project(libccoifits)

# Compile with C++11 support
ADD_DEFINITIONS("-std=c++0x -pthread")

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

add_subdirectory(src)
