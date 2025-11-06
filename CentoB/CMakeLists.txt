cmake_minimum_required(VERSION 3.28)

add_executable(CentoB
    "src/main.cpp" 
    "src/ArgsResolver.cpp" 
    "src/Log.cpp" 
    "src/ManifestFile.cpp"  
    "src/Utils.cpp" 
    "src/ManifestObjects.cpp"  
    "src/TargetStack.cpp" 
    "src/Targets/TargetRegistry.cpp" 
    "src/Targets/AutomationTarget.cpp" 
    "src/Targets/BuildTarget.cpp"
    "src/Targets/CppNinjaGccTarget.cpp"
    "src/Targets/CsDotnetTarget.cpp"
    "src/Targets/ExternalDependencyTarget.cpp"
    "src/Targets/GoGoTarget.cpp"
    "src/Targets/RsCargoTarget.cpp"
    "src/Tasks/BuildTasks/BuildCargoTask.cpp"
    "src/Tasks/BuildTasks/BuildDotnetTask.cpp" 
    "src/Tasks/BuildTasks/BuildGoTask.cpp"
    "src/Tasks/BuildTasks/BuildNinjaTask.cpp" 
    "src/Tasks/GenTasks/GenCargoTask.cpp"
    "src/Tasks/GenTasks/GenCppBridgeIface.cpp"
    "src/Tasks/GenTasks/GenCppBridgeImpl.cpp"
    "src/Tasks/GenTasks/GenCsBridgeIface.cpp"
    "src/Tasks/GenTasks/GenCsBridgeImpl.cpp"
    "src/Tasks/GenTasks/GenDotnetTask.cpp"
    "src/Tasks/GenTasks/GenGoBridgeIface.cpp"
    "src/Tasks/GenTasks/GenGoBridgeImpl.cpp"
    "src/Tasks/GenTasks/GenGoTask.cpp"
    "src/Tasks/GenTasks/GenNinjaGccTask.cpp"
    "src/Tasks/GenTasks/GenRsBridgeIface.cpp"
    "src/Tasks/GenTasks/GenRsBridgeImpl.cpp"
    "src/Tasks/AutomationTask.cpp"
    "src/Generators/NinjaGenerator.cpp" 
    "src/Generators/DotnetGenerator.cpp" "src/Generators/CargoGenerator.cpp" "src/Generators/GoGenerator.cpp")
target_include_directories(CentoB PRIVATE src)
set_target_properties(CentoB PROPERTIES CXX_STANDARD 23 CXX_STANDARD_REQUIRED ON)
set_target_properties(CentoB PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
target_link_libraries(CentoB PRIVATE figcone wildcards_lib rapidxml_lib)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(CentoB PRIVATE -fdiagnostics-color=always)
endif()
