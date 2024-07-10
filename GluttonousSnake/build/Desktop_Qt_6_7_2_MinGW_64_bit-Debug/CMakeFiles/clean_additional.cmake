# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\GluttonousSnake_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\GluttonousSnake_autogen.dir\\ParseCache.txt"
  "GluttonousSnake_autogen"
  )
endif()
