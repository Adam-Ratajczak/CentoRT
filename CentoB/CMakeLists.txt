cmake_minimum_required(VERSION 3.28)

add_executable(CentoB
    "src/main.cpp" 
    "src/ArgsResolver.cpp" 
    "src/Log.cpp" 
    "src/ManifestFile.cpp"  
    "src/Utils.cpp" 
    "src/ManifestObjects.cpp"  
    "src/TargetObjectStack.cpp" 
    "src/Targets/TargetObjectRegistry.cpp" 
    "src/Targets/AutomationTargetObject.cpp" 
    "src/Targets/CppNinjaTargetObject.cpp"
    "src/Targets/CppTargetObject.cpp"
    "src/Targets/CsDotnetTargetObject.cpp"
    "src/Targets/CsTargetObject.cpp"
    "src/Targets/ExternalDependencyTargetObject.cpp"
    "src/Targets/GoGoTargetObject.cpp"
    "src/Targets/GoTargetObject.cpp"
    "src/Targets/RsCargoTargetObject.cpp"
    "src/Targets/RsTargetObject.cpp"
)
target_include_directories(CentoB PRIVATE src)
set_target_properties(CentoB PROPERTIES CXX_STANDARD 23 CXX_STANDARD_REQUIRED ON)
set_target_properties(CentoB PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
target_link_libraries(CentoB PRIVATE figcone wildcards_lib)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(CentoB PRIVATE -fdiagnostics-color=always)
endif()
