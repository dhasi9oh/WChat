# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "FluentUI\\CMakeFiles\\fluentuiplugin_autogen.dir\\AutogenUsed.txt"
  "FluentUI\\CMakeFiles\\fluentuiplugin_autogen.dir\\ParseCache.txt"
  "FluentUI\\fluentuiplugin_autogen"
  "src\\CMakeFiles\\ChatClient_autogen.dir\\AutogenUsed.txt"
  "src\\CMakeFiles\\ChatClient_autogen.dir\\ParseCache.txt"
  "src\\ChatClient_autogen"
  )
endif()
