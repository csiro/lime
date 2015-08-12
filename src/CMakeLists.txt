include_directories(${PROJECT_INCLUDE_DIR})

file(GLOB HDR ${PROJECT_INCLUDE_DIR}/*.h)
file(GLOB SRC *.cc)

add_library(lime ${SRC} ${HDR})
