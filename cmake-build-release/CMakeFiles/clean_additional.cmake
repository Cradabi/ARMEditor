# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "ARM_autogen"
  "CMakeFiles/ARM_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ARM_autogen.dir/ParseCache.txt"
  "CMakeFiles/DBLib_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/DBLib_autogen.dir/ParseCache.txt"
  "CMakeFiles/ParserLib_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ParserLib_autogen.dir/ParseCache.txt"
  "CMakeFiles/PrimitivesLib_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/PrimitivesLib_autogen.dir/ParseCache.txt"
  "DBLib_autogen"
  "ParserLib_autogen"
  "PrimitivesLib_autogen"
  )
endif()
