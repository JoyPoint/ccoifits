cmake_minimum_required(VERSION 2.8)
project(ccoifits)

find_package(CCFITS REQUIRED)
include_directories(${CCFITS_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/calibrators)

file(GLOB CCOIFITS_SOURCE *.cpp calibrators/*.cpp)
file(GLOB MAIN_FILES main.cpp)
list(REMOVE_ITEM CCOIFITS_SOURCE ${MAIN_FILES})

#add_library(ccoifits_static STATIC ${CCOIFITS_SOURCE} ${CCFITS_LIBRARIES})
#target_link_libraries(ccoifits_static ${CCFITS_LIBRARIES})
add_library(ccoifits_shared SHARED ${CCOIFITS_SOURCE} ${CCFITS_LIBRARIES})
target_link_libraries(ccoifits_shared ${CCFITS_LIBRARIES})

add_executable(main ${MAIN_FILES})
target_link_libraries(main ccoifits_shared ${CCFITS_LIBRARIES})
