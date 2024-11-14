
set(PROJECT_NAME_TEST "${PROJECT_NAME}_test")
enable_testing()

add_executable(
	${PROJECT_NAME_TEST}
	audiodb.hpp
	audiodb.cpp
	audiodb_test.cpp
)

target_link_libraries(
	${PROJECT_NAME_TEST}
	GTest::gtest_main
	Qt::Core
)

set_target_properties(${PROJECT_NAME_TEST} PROPERTIES
  VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${QT_ROOT}bin;${QT_ROOT}plugins/platforms")

include(GoogleTest)
#gtest_discover_tests(${PROJECT_NAME_TEST})