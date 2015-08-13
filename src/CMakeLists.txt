include_directories(${PROJECT_INCLUDE_DIR})

file(GLOB SRC *.cc)

add_library(lime ${SRC})
