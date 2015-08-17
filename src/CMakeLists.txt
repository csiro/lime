include_directories(${PROJECT_INCLUDE_DIR})

file(GLOB SRC *.cc)
file(GLOB HDR ${PROJECT_INCLUDE_DIR}/lime/*.h)

add_library(lime ${SRC} ${HDR})
