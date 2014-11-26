cmake_minimum_required(VERSION 2.8)
project(ccoifits)

find_package(CCFITS REQUIRED)
include_directories(${CCFITS_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/calibrators)

# Export the inclusion directories:
set(CCOIFITS_INCLUDE_DIRS ${CCFITS_INCLUDE_DIR} CACHE INTERNAL "")

# Get a list of all source files in the directory
file(GLOB CCOIFITS_SOURCE *.cpp calibrators/*.cpp)

# List all of the unit tests, remove them from CCOIFITS_SOURCE
file(GLOB TEST_SOURCE ccoifits_tests.cpp *_test.cpp)
list(REMOVE_ITEM CCOIFITS_SOURCE ${TEST_SOURCE})

# List all of the executables, remove them from CCOIFITS_SOURCE
file(GLOB EXECUTABLE_SOURCE oiexport.cpp)
list(REMOVE_ITEM CCOIFITS_SOURCE ${EXECUTABLE_SOURCE})

add_library(ccoifits_static STATIC ${CCOIFITS_SOURCE} ${CCFITS_LIBRARIES})
target_link_libraries(ccoifits_static ${CCFITS_LIBRARIES})
set_target_properties(ccoifits_static PROPERTIES OUTPUT_NAME ccoifits)

add_library(ccoifits SHARED ${CCOIFITS_SOURCE} ${CCFITS_LIBRARIES})
target_link_libraries(ccoifits ${CCFITS_LIBRARIES})

add_executable(ccoifits_tests ${TEST_SOURCE})
target_link_libraries(ccoifits_tests gtest ccoifits_static ${CCFITS_LIBRARIES})

add_executable(oiexport oiexport.cpp)
target_link_libraries(oiexport ccoifits_static ${CCFITS_LIBRARIES})

install(TARGETS ccoifits DESTINATION lib)
install(FILES oi_file.hpp DESTINATION include)
install(FILES oi_tools.hpp DESTINATION include)
install(FILES oi_export.hpp DESTINATION include)
install(FILES oi_filter.hpp DESTINATION include)

# Automatic packaging
SET(CPACK_GENERATOR "DEB")
SET(CPACK_PACKAGE_NAME "ccoifits")
SET(CPACK_PACKAGE_VERSION 1.0.0)
SET(CPACK_PACKAGE_CONTACT "Brian Kloppenborg <bkloppenborg@gmail.com>")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++ OIFITS library (https://github.com/bkloppenborg/ccoifits)")

# Debian-specific packaging options
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libcfitsio3 ( >= 3.340 ), libccfits0 ( >= 2.4)")
 
INCLUDE(CPack)
