file(GLOB_RECURSE CENTORT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(CentoRT SHARED ${CENTORT_SOURCES})

target_include_directories(CentoRT
    PRIVATE
        include/
)
target_link_libraries(CentoRT
    PRIVATE
        CentoCommon
)

target_compile_features(CentoRT PUBLIC cxx_std_20)

target_compile_definitions(CentoRT PRIVATE CENTO_EXPORTS)

if(NOT WIN32)
    target_compile_options(CentoRT PRIVATE -fvisibility=hidden -fvisibility-inlines-hidden)
endif()

set_target_properties(CentoRT PROPERTIES
    OUTPUT_NAME "CentoRT"
    EXPORT_NAME "CentoRT"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/modules
)