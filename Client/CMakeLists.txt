cmake_minimum_required(VERSION 3.27)
project(ARM LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)
find_package(Qt5 COMPONENTS Sql REQUIRED)

#find_package(nlohmann_json 3.5.0 REQUIRED)

#find_package(PkgConfig)

#pkg_search_module(LIBPQ REQUIRED libpq)

add_library(PrimitivesLib STATIC primitives_lib/FiguresClasses.cpp primitives_lib/SchemeClass.cpp)

add_library(ParserLib STATIC parser_lib/src/SchemeParser.cpp parser_lib/src/SchemeObjectParser.cpp parser_lib/src/SchemeSectionsParser.cpp parser_lib/SchemeFileParser.cpp)

add_library(DBLib STATIC db_lib/DBManager.cpp)

add_library(ArmClientLib STATIC socket_client/lib/arm_client.cpp)

add_library(OrdersLib STATIC orders_lib/AutomaticOrder.cpp orders_lib/ManualOrder.cpp orders_lib/OrdersRepository.cpp)

add_library(Application STATIC application/MainView.cpp application/MainWidget.cpp application/MainWindow.cpp
        application/LoginDialog.cpp application/OrderWidget.cpp)

add_executable(${PROJECT_NAME} main.cpp)

#target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

#Подключаем QT к проекту
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Sql Qt5::Network ${LIBPQ_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

target_link_libraries(Application PRIVATE Qt5::Core Qt5::Sql Qt5::Widgets Qt5::Network ${LIBPQ_LIBRARIES})
#target_link_libraries(Application PRIVATE nlohmann_json::nlohmann_json)

#Подключаем QT к статической библиотеке PrimitivesLib
target_link_libraries(PrimitivesLib PRIVATE Qt5::Core Qt5::Sql ${LIBPQ_LIBRARIES})
target_link_libraries(PrimitivesLib PRIVATE Qt5::Widgets)

#Подключаем QT к статической библиотеке ParserLib
target_link_libraries(ParserLib PRIVATE Qt5::Core Qt5::Sql ${LIBPQ_LIBRARIES})
target_link_libraries(ParserLib PRIVATE Qt5::Widgets)

target_link_libraries(DBLib PRIVATE Qt5::Sql)
#target_link_libraries(DBLib PRIVATE nlohmann_json::nlohmann_json)

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