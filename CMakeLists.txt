project(Conway)
cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests unit_tests/tests.cpp lib/conway.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

add_executable(runCGol src/driver.cpp lib/conway.cpp)