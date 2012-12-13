cmake_minimum_required(VERSION 2.8)
project(ccoifits)

find_package(CCFITS REQUIRED)
include_directories(${CCFITS_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/calibrators)

# Export the inclusion directories:
set(CCOIFITS_INCLUDE_DIRS ${CCFITS_INCLUDE_DIR} CACHE INTERNAL "")

file(GLOB CCOIFITS_SOURCE *.cpp calibrators/*.cpp)
file(GLOB MAIN_FILES main.cpp PathFind.cpp)
list(REMOVE_ITEM CCOIFITS_SOURCE ${MAIN_FILES})

add_library(ccoifits_static STATIC ${CCOIFITS_SOURCE} ${CCFITS_LIBRARIES})
target_link_libraries(ccoifits_static ${CCFITS_LIBRARIES})
add_library(ccoifits SHARED ${CCOIFITS_SOURCE} ${CCFITS_LIBRARIES})
target_link_libraries(ccoifits ${CCFITS_LIBRARIES})

add_executable(ccoifits_tests ${MAIN_FILES})
target_link_libraries(ccoifits_tests ccoifits ${CCFITS_LIBRARIES})

install(TARGETS ccoifits DESTINATION lib)
install(FILES oi_file.hpp DESTINATION include)
install(FILES oi_tools.hpp DESTINATION include)
install(FILES oi_export.hpp DESTINATION include)
install(FILES oi_filter.hpp DESTINATION include)