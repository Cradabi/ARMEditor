cmake_minimum_required(VERSION 3.27)
project(ARM_driver_emulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)
find_package(Qt5 COMPONENTS Sql REQUIRED)

find_package(PkgConfig)
pkg_search_module(LIBPQ REQUIRED libpq)

add_library(EmulatorLib STATIC lib/driver_emulator.cpp)

add_executable(${PROJECT_NAME} driver_emulator_main.cpp)

#Подключаем QT к проекту
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Sql Qt5::Network ${LIBPQ_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Sql)

#Подключаем QT к статической библиотеке PrimitivesLib
target_link_libraries(EmulatorLib PRIVATE Qt5::Core Qt5::Sql Qt5::Network  ${LIBPQ_LIBRARIES})
target_link_libraries(EmulatorLib PRIVATE Qt5::Widgets)


#Подключаем ParserLib к проекту
target_link_libraries(${PROJECT_NAME} PRIVATE EmulatorLib)
