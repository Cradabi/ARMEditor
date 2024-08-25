# Установим минимальную требуемую версию CMake
cmake_minimum_required(VERSION 3.14)

# Название проекта
project(DBLibTests LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Включаем поддержку автоматического вызова MOC, UIC и RCC для Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(GTest REQUIRED)
include(GoogleTest)

if(NOT TARGET GTest::gmock)
    find_library(GMOCK_LIBRARY gmock)
    find_library(GMOCK_MAIN_LIBRARY gmock_main)
    add_library(GTest::gmock UNKNOWN IMPORTED)
    set_target_properties(GTest::gmock PROPERTIES
            IMPORTED_LOCATION "${GMOCK_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${GTEST_INCLUDE_DIRS}"
            )
    add_library(GTest::gmock_main UNKNOWN IMPORTED)
    set_target_properties(GTest::gmock_main PROPERTIES
            IMPORTED_LOCATION "${GMOCK_MAIN_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${GTEST_INCLUDE_DIRS}"
            )
endif()

include_directories(${GTEST_INCLUDE_DIRS})




# Ищем и подключаем Qt
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Sql REQUIRED)

# Ищем и подключаем libpq через pkg-config
find_package(PkgConfig)
pkg_search_module(LIBPQ REQUIRED libpq)

# Добавляем исходные файлы тестов
set(TEST_SOURCES
        mock_test_db_connection.cpp
        )

# Создаем исполняемый файл для тестов
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

# Подключаем необходимые библиотеки к тестовому проекту
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Sql ${LIBPQ_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE
        GTest::GTest
        GTest::Main
        GTest::gmock
        GTest::gmock_main
        )
# Подключаем тестируемую библиотеку DBLib
target_link_libraries(${PROJECT_NAME} PRIVATE DBLib)

# Включаем тесты
gtest_discover_tests(${PROJECT_NAME})
enable_testing()
add_test(NAME DBLibTests COMMAND ${PROJECT_NAME})