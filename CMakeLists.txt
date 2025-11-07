cmake_minimum_required(VERSION 3.28)
project(CentoRTProject VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(figcone
    GIT_REPOSITORY https://github.com/kamchatka-volcano/figcone.git
    GIT_TAG master
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    figcone)
FetchContent_MakeAvailable(figcone)

FetchContent_Declare(wildcards
  GIT_REPOSITORY https://github.com/zemasoft/wildcards.git
  GIT_TAG        master
  GIT_SHALLOW    ON
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(wildcards)

FetchContent_GetProperties(wildcards)
if(NOT wildcards_POPULATED)
  FetchContent_Populate(wildcards)
endif()

add_library(wildcards_lib INTERFACE)

target_include_directories(wildcards_lib INTERFACE
  ${wildcards_SOURCE_DIR}/include
)
FetchContent_Declare(
    rapidxml
    GIT_REPOSITORY https://github.com/dwd/rapidxml.git
    GIT_TAG        v1.0.0
)

FetchContent_MakeAvailable(rapidxml)

add_library(rapidxml_lib INTERFACE)
target_include_directories(rapidxml_lib INTERFACE
    ${rapidxml_SOURCE_DIR}
)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CentoB)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CentoCommon)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CentoRT)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CentoLib)
