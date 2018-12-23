
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
include_directories(../)

target_link_libraries(Footest ${GTEST_BOTH_LIBRARIES})

add_test(
  NAME Footest
  COMMAND Footest
  )


