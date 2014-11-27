cmake_minimum_required(VERSION 2.8) 
project(libccoifits)

# get version information from git
INCLUDE("${CMAKE_SOURCE_DIR}/CMakeModules/SetVersion.cmake")

# Compile with C++11 support.  Disable __STRICT_ANSI__ to support 
# some nice OpenCL shortcuts (i.e. cl_float2's .s0, .s1 syntax).
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
SET(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")

LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules")

# Include and build Google Test framework:
if(NOT TARGET gtest)
    ADD_SUBDIRECTORY (lib/gtest-1.6.0)
    enable_testing()
endif(NOT TARGET gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# build subdirectories
add_subdirectory(src)

# Install stage
INSTALL_FILES("${CMAKE_ROOT}/Modules" FILES "${CMAKE_SOURCE_DIR}/FindCCOIFITS.cmake")

# Get the architecture
EXECUTE_PROCESS(
    COMMAND dpkg --print-architecture
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE OS_ARCHITECTURE
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Automatic packaging
SET(CPACK_GENERATOR "DEB")
SET(CPACK_PACKAGE_NAME "ccoifits")
SET(CPACK_PACKAGE_VERSION ${GIT_VERSION_TAG})
SET(CPACK_PACKAGE_CONTACT "Brian Kloppenborg <bkloppenborg@gmail.com>")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++ OIFITS library (https://github.com/bkloppenborg/ccoifits)")

# Debian-specific packaging options
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libcfitsio3 ( >= 3.340 ), libccfits0 ( >= 2.4)")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${OS_ARCHITECTURE})
SET(CPACK_DEBIAN_PACKAGE_SECTION "devel")

# Run CPack
INCLUDE(CPack)
