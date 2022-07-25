cmake_minimum_required(VERSION 3.5)

project(plane_board VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Svg)

find_library(IIO_LIBRARIES iio)
find_path(IIO_INCLUDE_DIRS iio.h)

find_library(QFI_LIBRARIES qfi REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

FILE(GLOB PROJECT_SOURCES
    *.cpp
    *.h
    *.ui
    qfi/*.cpp
    qfi/*.h
    qfi/*.pri
)

add_executable(plane_board
    ${PROJECT_SOURCES}
)

target_include_directories(plane_board PUBLIC
    ${IIO_INCLUDE_DIRS}
    ${QFI_INCLUDE_DIRS})

target_link_libraries(plane_board PRIVATE
    ${QFI_LIBRARIES}
    ${IIO_LIBRARIES}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Svg)

set_target_properties(plane_board PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(plane_board)
endif()
