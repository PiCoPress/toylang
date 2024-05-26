add_executable(test1 test.cpp)
include(GoogleTest)
target_link_libraries(test1 GTest::gtest_main libpack)

gtest_discover_tests(test1)