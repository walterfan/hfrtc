add_executable(TinyChartTest TinyChartTest.cpp)
target_link_libraries(TinyChartTest tinyutil gd)

add_executable(UnitTest UnitTest.cpp server_test.cpp lua_test.cpp TinyUtilTest.cpp  TinyConfigTest.cpp)
target_link_libraries(UnitTest tinyutil gtest gmock lua)