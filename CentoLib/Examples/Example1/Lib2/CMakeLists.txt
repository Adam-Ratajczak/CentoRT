cmake_minimum_required(VERSION 3.28)

add_library(Lib2 SHARED src/dllmain.cpp)

target_link_libraries(Lib1
    PRIVATE
        CentoLib
)

target_compile_features(Lib2 PUBLIC cxx_std_20)
target_compile_definitions(Lib2 PRIVATE LIB1_EXPORTS)

if(NOT WIN32)
    target_compile_options(Lib2 PRIVATE -fvisibility=hidden -fvisibility-inlines-hidden)
endif()

set_target_properties(Lib2 PROPERTIES
    OUTPUT_NAME "Lib2"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Example1
)
