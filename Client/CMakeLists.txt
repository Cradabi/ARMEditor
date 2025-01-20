cmake_minimum_required(VERSION 3.27)
project(ARM LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)
find_package(Qt5 COMPONENTS Sql REQUIRED)

find_package(PkgConfig)
pkg_search_module(LIBPQ REQUIRED libpq)

add_library(PrimitivesLib STATIC primitives_lib/FiguresClasses.cpp primitives_lib/SchemeClass.cpp)

add_library(ParserLib STATIC parser_lib/src/SchemeParser.cpp parser_lib/src/SchemeObjectParser.cpp parser_lib/src/SchemeSectionsParser.cpp parser_lib/SchemeFileParser.cpp)

add_library(DBLib STATIC db_lib/db_connection.cpp)

add_library(ArmClientLib STATIC socket_client/lib/arm_client.cpp)

add_library(Application STATIC application/myview.cpp application/mywidget.cpp application/mainwindow.cpp
        application/LoginDialog.cpp)

add_executable(${PROJECT_NAME} main.cpp)

#Подключаем QT к проекту
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Sql Qt5::Network ${LIBPQ_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

target_link_libraries(Application PRIVATE Qt5::Core Qt5::Sql Qt5::Widgets Qt5::Network ${LIBPQ_LIBRARIES})

#Подключаем QT к статической библиотеке PrimitivesLib
target_link_libraries(PrimitivesLib PRIVATE Qt5::Core Qt5::Sql ${LIBPQ_LIBRARIES})
target_link_libraries(PrimitivesLib PRIVATE Qt5::Widgets)

#Подключаем QT к статической библиотеке ParserLib
target_link_libraries(ParserLib PRIVATE Qt5::Core Qt5::Sql ${LIBPQ_LIBRARIES})
target_link_libraries(ParserLib PRIVATE Qt5::Widgets)

target_link_libraries(DBLib PRIVATE Qt5::Sql)

target_link_libraries(ArmClientLib PRIVATE Qt5::Core Qt5::Sql Qt5::Network ${LIBPQ_LIBRARIES})

#Подключаем ParserLib к проекту
target_link_libraries(${PROJECT_NAME} PRIVATE DBLib)

target_link_libraries(Application PRIVATE DBLib)

target_link_libraries(${PROJECT_NAME} PRIVATE Application)

#Подключаем ParserLib к проекту
target_link_libraries(${PROJECT_NAME} PRIVATE ParserLib)

#Подключаем PrimitivesLib к проекту
target_link_libraries(${PROJECT_NAME} PRIVATE PrimitivesLib)

target_link_libraries(${PROJECT_NAME} PRIVATE ArmClientLib)