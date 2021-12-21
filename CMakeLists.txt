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
set(EXE_EXT "")
IF(${CMAKE_SYSTEM_NAME} STREQUAL CYGWIN)
  set(EXE_EXT ".exe")
ENDIF()
message(STATUS "os is ${CMAKE_SYSTEM_NAME}")
message(STATUS "exe ext is ${EXE_EXT}")

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
	${PROJECT_SOURCE_DIR}/src/fileutil.cc
	${PROJECT_SOURCE_DIR}/src/geomutil.cc
	${PROJECT_SOURCE_DIR}/src/indexchoice.cc
	${PROJECT_SOURCE_DIR}/src/intset.cc
	${PROJECT_SOURCE_DIR}/src/limetok.cc
	${PROJECT_SOURCE_DIR}/src/lockfile.cc
	${PROJECT_SOURCE_DIR}/src/numutil.cc
	${PROJECT_SOURCE_DIR}/src/opts.cc
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
	${PROJECT_SOURCE_DIR}/src/splitter.cc
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
	${PROJECT_INCLUDE_DIR}/lime/fileutil.h
	${PROJECT_INCLUDE_DIR}/lime/geomutil.h
	${PROJECT_INCLUDE_DIR}/lime/hillclimb.h
	${PROJECT_INCLUDE_DIR}/lime/indexchoice.h
	${PROJECT_INCLUDE_DIR}/lime/indexmap.h
	${PROJECT_INCLUDE_DIR}/lime/indexstack.h
	${PROJECT_INCLUDE_DIR}/lime/intset.h
	${PROJECT_INCLUDE_DIR}/lime/limetok.h
	${PROJECT_INCLUDE_DIR}/lime/line.h
	${PROJECT_INCLUDE_DIR}/lime/lockfile.h
	${PROJECT_INCLUDE_DIR}/lime/numutil.h
	${PROJECT_INCLUDE_DIR}/lime/opts.h
	${PROJECT_INCLUDE_DIR}/lime/permutation.h
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
add_executable(limetest${EXE_EXT}
	EXCLUDE_FROM_ALL
	${PROJECT_SOURCE_DIR}/test/limetest.cc
)
target_link_libraries(limetest${EXE_EXT} lime)

## Accessor Test
add_executable(accessortest${EXE_EXT}
	EXCLUDE_FROM_ALL
	${PROJECT_TEST_DIR}/accessortest.cc
)
target_link_libraries(accessortest${EXE_EXT} lime)

## Box Test
add_executable(boxtest${EXE_EXT}
	EXCLUDE_FROM_ALL
	${PROJECT_TEST_DIR}/boxtest.cc
)
target_link_libraries(boxtest${EXE_EXT} lime)

## Opt Test
add_executable(opttest${EXE_EXT}
	EXCLUDE_FROM_ALL
	${PROJECT_TEST_DIR}/opttest.cc
)
target_link_libraries(opttest${EXE_EXT} lime)

## Permutation Test
add_executable(permtest${EXE_EXT}
	EXCLUDE_FROM_ALL
	${PROJECT_TEST_DIR}/permtest.cc
)
target_link_libraries(permtest${EXE_EXT} lime)

## Splitter Test
add_executable(splitest${EXE_EXT}
	EXCLUDE_FROM_ALL
	${PROJECT_TEST_DIR}/splitest.cc
)
target_link_libraries(splitest${EXE_EXT} lime)

## PWL Test
add_executable(pwltest${EXE_EXT}
	EXCLUDE_FROM_ALL
	${PROJECT_TEST_DIR}/pwltest.cc
)
target_link_libraries(pwltest${EXE_EXT} lime)

## hilbert 
add_executable(hilbert${EXE_EXT}
	EXCLUDE_FROM_ALL
	${PROJECT_TEST_DIR}/hilbert.cc
)
target_link_libraries(hilbert${EXE_EXT} lime)

## File Test
add_executable(filetest${EXE_EXT}
	EXCLUDE_FROM_ALL
	${PROJECT_SOURCE_DIR}/test/filetest.cc
)
target_link_libraries(filetest${EXE_EXT} lime)

## Custom target for all tests
add_custom_target(tests)
add_dependencies(tests
	limetest${EXE_EXT}
	boxtest${EXE_EXT}
	opttest${EXE_EXT}
	accessortest${EXE_EXT}
	pwltest${EXE_EXT}
	filetest${EXE_EXT}
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
    TARGETS limetest${EXE_EXT} accessortest${EXE_EXT} boxtest${EXE_EXT} opttest${EXE_EXT} pwltest${EXE_EXT} 
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
