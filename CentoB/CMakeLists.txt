cmake_minimum_required(VERSION 3.28)

add_executable(CentoB
    src/main.cpp "src/ArgsResolver.cpp" "src/Log.cpp")
set_target_properties(CentoB PROPERTIES CXX_STANDARD 23 CXX_STANDARD_REQUIRED ON)
set_target_properties(CentoB PROPERTIES
  VS_DEBUGGER_COMMAND_ARGUMENTS "dump"
  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
target_link_libraries(CentoB PRIVATE figcone)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(CentoB PRIVATE -fdiagnostics-color=always)
endif()
