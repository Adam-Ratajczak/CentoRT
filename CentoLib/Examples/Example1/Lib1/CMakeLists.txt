cmake_minimum_required(VERSION 3.28)

add_library(Lib1 SHARED src/dllmain.cpp)

target_link_libraries(Lib1
    PRIVATE
        CentoLib
)

target_compile_features(Lib1 PUBLIC cxx_std_20)
target_compile_definitions(Lib1 PRIVATE LIB1_EXPORTS)

if(NOT WIN32)
    target_compile_options(Lib1 PRIVATE -fvisibility=hidden -fvisibility-inlines-hidden)
endif()

set_target_properties(Lib1 PROPERTIES
    OUTPUT_NAME "Lib1"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Example1
)
