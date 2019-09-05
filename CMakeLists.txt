cmake_minimum_required(VERSION 2.8.4)

project(Lime C CXX)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

# Set some flags
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -ggdb -pg")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -march=native -DNDEBUG")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols")

# Set directories
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_BUILD_TYPE "Release")

set (LASTBUILD_DIR ${PROJECT_SOURCE_DIR}/src)
set (LASTBUILD_CMD ${PROJECT_SOURCE_DIR}/util/lastbuildc)
set (LASTBUILD_CC ${LASTBUILD_DIR}/lastbuild.cc)

add_subdirectory(src)
add_subdirectory(test)
