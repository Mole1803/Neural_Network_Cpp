project(GoogleTest)
# 'lib' is the folder with Google Test sources
add_subdirectory(lib/googletest-1.13.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run test_matrix.cpp ../matrix.h ../matrix.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)