
qt_add_executable(${PROJECT_NAME}
	mainwindow.cpp
	mainwindow.hpp
	mainwindow.ui
	settingswidget.cpp
	settingswidget.hpp
	settingswidget.ui
	task.cpp
	task.hpp
	tasktablemodel.cpp
	tasktablemodel.hpp
	taskwidget.cpp
	taskwidget.hpp
	taskwidget.ui
	timedisplaywidget.cpp
	timedisplaywidget.hpp
	timerwidget.cpp
	timerwidget.hpp
	timerwidget.ui
	tomatotimer.cpp
	tomatotimer.hpp
	main.cpp
)

qt_add_resources(${PROJECT_NAME} "qmato"
    PREFIX "/"
    FILES
        resources/audio/kitchen-ring.wav
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
	Qt::Core
	Qt::Gui
	Qt::Widgets
	Qt::Multimedia)
	
if(MSVC)
	target_compile_options(${PROJECT_NAME} PUBLIC /MP)
endif()


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