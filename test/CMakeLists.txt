include_directories(${PROJECT_INCLUDE_DIR})

file(GLOB RC_SRC lastbuild.cc readconfig.cc)
file(GLOB A_SRC accessortest.cc)
file(GLOB P_SRC pwltest.cc)

add_executable(limetest ${RC_SRC})
target_link_libraries(limetest lime)

add_executable(accessortest ${A_SRC})
target_link_libraries(accessortest lime)

add_executable(pwltest ${P_SRC})
target_link_libraries(pwltest lime)
