cmake_minimum_required(VERSION 3.28)

file(GLOB_RECURSE LIBCENTO_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(CentoLib STATIC ${LIBCENTO_SOURCES})

target_include_directories(CentoLib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inl
)
target_link_libraries(CentoLib
    PRIVATE
        CentoCommon

)

target_compile_features(CentoLib PUBLIC cxx_std_20)

set_target_properties(CentoLib PROPERTIES
    OUTPUT_NAME "cento"
    EXPORT_NAME "Cento"
)

include(GNUInstallDirs)

install(
    TARGETS CentoLib
    EXPORT LibCentoTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_subdirectory(Examples)
