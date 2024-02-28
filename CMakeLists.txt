cmake_minimum_required(VERSION 3.5)

project(ARM LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME}
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mywidget.h
        mainwindow.ui
)


add_library(figures)
add_library(parser)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
target_include_directories(${PROJECT_NAME} PUBLIC $ {PROJECT_SOURCE_DIR})
