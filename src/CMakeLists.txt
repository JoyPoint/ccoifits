cmake_minimum_required(VERSION 2.8)
project(ccoifits)

find_package(CCFITS REQUIRED)
include_directories(${CCFITS_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/calibrators)

# Export the inclusion directories:
set(CCOIFITS_INCLUDE_DIRS ${CCFITS_INCLUDE_DIR} CACHE INTERNAL "")

file(GLOB CCOIFITS_SOURCE *.cpp calibrators/*.cpp)
file(GLOB MAIN_FILES main.cpp)
list(REMOVE_ITEM CCOIFITS_SOURCE ${MAIN_FILES})

add_library(ccoifits_static STATIC ${CCOIFITS_SOURCE} ${CCFITS_LIBRARIES})
target_link_libraries(ccoifits_static ${CCFITS_LIBRARIES})
add_library(ccoifits SHARED ${CCOIFITS_SOURCE} ${CCFITS_LIBRARIES})
target_link_libraries(ccoifits ${CCFITS_LIBRARIES})

add_executable(ccoifits_tests ${MAIN_FILES})
target_link_libraries(ccoifits_tests ccoifits ${CCFITS_LIBRARIES})

install(TARGETS ccoifits DESTINATION lib)
install(FILES COIFile.h DESTINATION include RENAME ccoifits.hpp)
install(FILES OITools.h DESTINATION include RENAME oi_tools.hpp)
install(FILES OIExport.h DESTINATION include RENAME oi_export.hpp)
