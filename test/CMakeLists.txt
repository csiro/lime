include_directories(${PROJECT_INCLUDE_DIR})

file(GLOB SRC *.cc)

add_executable(limetest ${SRC})
target_link_libraries(limetest lime)
