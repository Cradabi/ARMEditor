cmake_minimum_required(VERSION 3.27)
project(ARM_driver_emulator LANGUAGES CXX)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 23)

# Включение автоматической обработки Qt файлов
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)  # Генерация .ui файлов
set(CMAKE_AUTOMOC ON)  # Генерация moc-файлов
set(CMAKE_AUTORCC ON)  # Генерация rcc-файлов

# Поиск необходимых компонентов Qt
find_package(Qt5 COMPONENTS Widgets Network Sql REQUIRED)

# Поиск библиотеки libpq
find_package(PkgConfig)
pkg_search_module(LIBPQ REQUIRED libpq)

# Добавление исходников и библиотек
add_library(EmulatorLib STATIC lib/driver_emulator.cpp)

# Добавление главного приложения
add_executable(${PROJECT_NAME}
        driver_emulator_main.cpp
        mainwindow.cpp
        mainwindow.ui
)

# Подключение Qt библиотек к главному проекту
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets Qt5::Network Qt5::Sql ${LIBPQ_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE EmulatorLib)

# Подключение Qt библиотек к библиотеке EmulatorLib
target_link_libraries(EmulatorLib PRIVATE Qt5::Core Qt5::Widgets Qt5::Network Qt5::Sql ${LIBPQ_LIBRARIES})

# Установка необходимых директорий
target_include_directories(${PROJECT_NAME} PRIVATE ../driver_emulator)
target_include_directories(EmulatorLib PRIVATE lib)

# Генерация файлов для пользовательского интерфейса
qt5_wrap_ui(UI_HEADERS mainwindow.ui)