cmake_minimum_required(VERSION 3.16)

include(FetchContent)

project(qmato VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia)
qt_standard_project_setup()

FetchContent_Declare(
    googletest
	URL https://github.com/google/googletest/archive/refs/heads/main.zip
    FIND_PACKAGE_ARGS
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)


