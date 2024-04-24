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
find_package(Qt5 COMPONENTS Sql REQUIRED)

find_package(PkgConfig)
pkg_search_module(LIBPQ REQUIRED libpq)

add_executable(${PROJECT_NAME}
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mywidget.h
        mainwindow.ui
)


add_library(figures)
add_library(parser)
add_library(bmp_file)
add_library(db)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Sql ${LIBPQ_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Sql)
target_include_directories(${PROJECT_NAME} PUBLIC $ {PROJECT_SOURCE_DIR})