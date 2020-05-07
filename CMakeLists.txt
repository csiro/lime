cmake_minimum_required(VERSION 3.0.2)

project(Lime 
		VERSION 0.1
		LANGUAGES CXX C)


#------------------------------------------------------------------------------#
# Compilation options

option(STATIC "compile with the -static linker flag" OFF)

#------------------------------------------------------------------------------#
# Compiler Configuration

## Static build
if(STATIC)
	set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

## Build Type 
##(Note that Visual Studio can build multiple build types at once and thus the build type need
## to be specified with the parameter --config when building, e.g., cmake --build . --config Release.)
set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
	# Set the possible values of build type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
		"Debug"
		"Release"
		"MinSizeRel"
		"RelWithDebInfo"
	)
endif()
if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}")
endif()

## C++ Standard
set(CMAKE_CXX_STANDARD 11)

#------------------------------------------------------------------------------#
# Set directories

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_TEST_DIR ${PROJECT_SOURCE_DIR}/test)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "PROJECT_INCLUDE_DIR: ${PROJECT_INCLUDE_DIR}")
message(STATUS "PROJECT_TEST_DIR: ${PROJECT_TEST_DIR}")

#------------------------------------------------------------------------------#
# Lime library

set(LIME_SOURCE_CFILES 
	${PROJECT_SOURCE_DIR}/src/accessor.cc
	${PROJECT_SOURCE_DIR}/src/adaptchoice.cc
	${PROJECT_SOURCE_DIR}/src/biaschoice.cc
	${PROJECT_SOURCE_DIR}/src/boundingbox.cc
	${PROJECT_SOURCE_DIR}/src/box.cc
	${PROJECT_SOURCE_DIR}/src/config.cc
	${PROJECT_SOURCE_DIR}/src/configreader.cc
	${PROJECT_SOURCE_DIR}/src/debug.cc
	${PROJECT_SOURCE_DIR}/src/dig.cc
	${PROJECT_SOURCE_DIR}/src/displayable.cc
	${PROJECT_SOURCE_DIR}/src/dznreader.cc
	${PROJECT_SOURCE_DIR}/src/dznwriter.cc
	${PROJECT_SOURCE_DIR}/src/error.cc
	${PROJECT_SOURCE_DIR}/src/geomutil.cc
	${PROJECT_SOURCE_DIR}/src/indexchoice.cc
	${PROJECT_SOURCE_DIR}/src/limetok.cc
	${PROJECT_SOURCE_DIR}/src/lockfile.cc
	${PROJECT_SOURCE_DIR}/src/numutil.cc
	${PROJECT_SOURCE_DIR}/src/point.cc
	${PROJECT_SOURCE_DIR}/src/progressbar.cc
	${PROJECT_SOURCE_DIR}/src/pwl.cc
	${PROJECT_SOURCE_DIR}/src/rand.cc
	${PROJECT_SOURCE_DIR}/src/randgen.cc
	${PROJECT_SOURCE_DIR}/src/randnew.cc
	${PROJECT_SOURCE_DIR}/src/reader.cc
	${PROJECT_SOURCE_DIR}/src/resource.cc
	${PROJECT_SOURCE_DIR}/src/resourcehandler.cc
	${PROJECT_SOURCE_DIR}/src/scheduler.cc
	${PROJECT_SOURCE_DIR}/src/shortestpath.cc
	${PROJECT_SOURCE_DIR}/src/shuffle.cc
	${PROJECT_SOURCE_DIR}/src/stat.cc
	${PROJECT_SOURCE_DIR}/src/strutil.cc
	${PROJECT_SOURCE_DIR}/src/timekeeper.cc
)

set(LIME_SOURCE_HEADERS 
	${PROJECT_INCLUDE_DIR}/lime/acceptmeth.h
	${PROJECT_INCLUDE_DIR}/lime/accessor.h
	${PROJECT_INCLUDE_DIR}/lime/activeobject.h
	${PROJECT_INCLUDE_DIR}/lime/adaptcfg.h
	${PROJECT_INCLUDE_DIR}/lime/adaptchoice.h
	${PROJECT_INCLUDE_DIR}/lime/biaschoice.h
	${PROJECT_INCLUDE_DIR}/lime/boundingbox.h
	${PROJECT_INCLUDE_DIR}/lime/box.h
	${PROJECT_INCLUDE_DIR}/lime/config.h
	${PROJECT_INCLUDE_DIR}/lime/configreader.h
	${PROJECT_INCLUDE_DIR}/lime/constants.h
	${PROJECT_INCLUDE_DIR}/lime/debug.h
	${PROJECT_INCLUDE_DIR}/lime/dig.h
	${PROJECT_INCLUDE_DIR}/lime/displayable.h
	${PROJECT_INCLUDE_DIR}/lime/dznreader.h
	${PROJECT_INCLUDE_DIR}/lime/dznwriter.h
	${PROJECT_INCLUDE_DIR}/lime/error.h
	${PROJECT_INCLUDE_DIR}/lime/geomutil.h
	${PROJECT_INCLUDE_DIR}/lime/hillclimb.h
	${PROJECT_INCLUDE_DIR}/lime/indexchoice.h
	${PROJECT_INCLUDE_DIR}/lime/indexmap.h
	${PROJECT_INCLUDE_DIR}/lime/indexstack.h
	${PROJECT_INCLUDE_DIR}/lime/limearr.h
	${PROJECT_INCLUDE_DIR}/lime/limetok.h
	${PROJECT_INCLUDE_DIR}/lime/line.h
	${PROJECT_INCLUDE_DIR}/lime/lockfile.h
	${PROJECT_INCLUDE_DIR}/lime/numutil.h
	${PROJECT_INCLUDE_DIR}/lime/point.h
	${PROJECT_INCLUDE_DIR}/lime/progressbar.h
	${PROJECT_INCLUDE_DIR}/lime/progresslistener.h
	${PROJECT_INCLUDE_DIR}/lime/pwl.h
	${PROJECT_INCLUDE_DIR}/lime/rand.h
	${PROJECT_INCLUDE_DIR}/lime/randgen.h
	${PROJECT_INCLUDE_DIR}/lime/randnew.h
	${PROJECT_INCLUDE_DIR}/lime/reader.h
	${PROJECT_INCLUDE_DIR}/lime/resource.h
	${PROJECT_INCLUDE_DIR}/lime/resourcehandler.h
	${PROJECT_INCLUDE_DIR}/lime/scheduler.h
	${PROJECT_INCLUDE_DIR}/lime/shortestpath.h
	${PROJECT_INCLUDE_DIR}/lime/shuffle.h
	${PROJECT_INCLUDE_DIR}/lime/simanneal.h
	${PROJECT_INCLUDE_DIR}/lime/sortpair.h
	${PROJECT_INCLUDE_DIR}/lime/spnode.h
	${PROJECT_INCLUDE_DIR}/lime/stat.h
	${PROJECT_INCLUDE_DIR}/lime/strutil.h
	${PROJECT_INCLUDE_DIR}/lime/timekeeper.h
	${PROJECT_INCLUDE_DIR}/lime/whirl.h
)

add_library(lime 
	${LIME_SOURCE_CFILES}
	${LIME_SOURCE_HEADERS}
)

target_include_directories(lime PUBLIC ${PROJECT_INCLUDE_DIR})

#------------------------------------------------------------------------------#
# Tests

## Lime Test
add_executable(limetest
	EXCLUDE_FROM_ALL
	${PROJECT_SOURCE_DIR}/test/limetest.cc
)
target_link_libraries(limetest lime)

## Accessor Test
add_executable(accessortest
	EXCLUDE_FROM_ALL
	${PROJECT_TEST_DIR}/accessortest.cc
)
target_link_libraries(accessortest lime)

## Box Test
add_executable(boxtest
	EXCLUDE_FROM_ALL
	${PROJECT_TEST_DIR}/boxtest
)
target_link_libraries(boxtest lime)

## PWL Test
add_executable(pwltest 
	EXCLUDE_FROM_ALL
	${PROJECT_TEST_DIR}/pwltest.cc
)
target_link_libraries(pwltest lime)

## hilbert 
add_executable(hilbert
	EXCLUDE_FROM_ALL
	${PROJECT_TEST_DIR}/hilbert.cc
)
target_link_libraries(hilbert lime)

## Custom target for all tests
add_custom_target(tests)
add_dependencies(tests
	limetest
	boxtest
	accessortest
	pwltest
)

#------------------------------------------------------------------------------#
# Install

install(
    TARGETS lime 
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(
    DIRECTORY ${PROJECT_INCLUDE_DIR}/lime 
    DESTINATION include 
    MESSAGE_NEVER
)
install(
    TARGETS limetest accessortest boxtest pwltest 
    RUNTIME DESTINATION bin 
    OPTIONAL
)

install(CODE "MESSAGE(\"\n\
Lime was successfully installed in '${CMAKE_INSTALL_PREFIX}'. \
Do not forget to add its sub-folders 'bin', 'include', and 'lib' to corresponding \
environment variables, e.g., PATH.
\")")

message(STATUS "Lime will be installed in '${CMAKE_INSTALL_PREFIX}'. \
Do not forget to add its sub-folders 'bin', 'include', and 'lib' to corresponding \
environment variables, e.g., PATH.
")
