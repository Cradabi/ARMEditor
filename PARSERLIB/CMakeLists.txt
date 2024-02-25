cmake_minimum_required(VERSION 3.21)

project(ARMEditor)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(parser)

add_executable(${PROJECT_NAME} parser.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE parser)
target_include_directories(${PROJECT_NAME} PUBLIC $ {PROJECT_SOURCE_DIR})
