# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "ARM_autogen"
  "CMakeFiles/ARM_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ARM_autogen.dir/ParseCache.txt"
  "CMakeFiles/bmp_file_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/bmp_file_autogen.dir/ParseCache.txt"
  "CMakeFiles/figures_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/figures_autogen.dir/ParseCache.txt"
  "CMakeFiles/parser_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/parser_autogen.dir/ParseCache.txt"
  "bmp_file_autogen"
  "figures_autogen"
  "parser_autogen"
  )
endif()
