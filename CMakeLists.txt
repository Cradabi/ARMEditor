cmake_minimum_required(VERSION 3.27)
project(ARM LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Sql REQUIRED)

find_package(PkgConfig)
pkg_search_module(LIBPQ REQUIRED libpq)

add_executable(${PROJECT_NAME} main.cpp interface/myview.cpp interface/mywidget.cpp interface/mainwindow.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Sql ${LIBPQ_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Sql)
target_include_directories(${PROJECT_NAME} PUBLIC $ {PROJECT_SOURCE_DIR})