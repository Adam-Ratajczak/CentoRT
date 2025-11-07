cmake_minimum_required(VERSION 3.28)

set(SRC_FILES
    src/DllFile.cpp
)

if (WIN32)
    list(APPEND SRC_FILES src/DllFileWin.cpp)
elseif(UNIX)
    list(APPEND SRC_FILES src/DllFileUnix.cpp)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

add_library(CentoCommon STATIC ${SRC_FILES})

target_include_directories(CentoCommon
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(CentoCommon PUBLIC cxx_std_20)

set_target_properties(CentoCommon PROPERTIES
    EXPORT_NAME "CentoCommon"
    EXPORT_EXCLUDE_FROM_ALL TRUE
)