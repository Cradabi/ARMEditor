cmake_minimum_required(VERSION 3.26)
project(ARMEditor)

set(CMAKE_CXX_STANDARD 14)

add_executable(ARMEditor
        simple_parser.cpp SchemeFileParser.h)
