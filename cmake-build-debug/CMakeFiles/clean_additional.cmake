# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Play_With_Fire_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Play_With_Fire_autogen.dir\\ParseCache.txt"
  "Play_With_Fire_autogen"
  )
endif()
