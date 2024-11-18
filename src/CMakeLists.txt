
qt_add_executable(${PROJECT_NAME}
    main.cpp
	mainwindow.cpp
	mainwindow.hpp
	mainwindow.ui
	tomatotimer.cpp
	tomatotimer.hpp
	timerwidget.ui
	timerwidget.hpp
	timerwidget.cpp
	settingswidget.ui
	settingswidget.hpp
	settingswidget.cpp
	timedisplaywidget.hpp
	timedisplaywidget.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
	Qt::Core
	Qt::Gui
	Qt::Widgets)


set_target_properties(${PROJECT_NAME} PROPERTIES
  VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${QT_ROOT}/bin;${QT_ROOT}/plugins/platforms")
  
get_property(_isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(_isMultiConfig)
  set(AUTOGEN_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_autogen/include_$<CONFIG>)
else()
  set(AUTOGEN_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_autogen/include)
endif()

target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${AUTOGEN_INCLUDE_DIR}>
)