enable_testing()
include(CTest)
find_package(GTest REQUIRED)
add_executable(tests
        DrawTest.cc
        OptionsTest.cc
        ParseTest.cc
        )
target_link_libraries(tests draw gtest pthread gtest_main)
add_custom_target(test COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS tests)
gtest_discover_tests(tests)
