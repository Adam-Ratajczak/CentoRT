cmake_minimum_required(VERSION 3.28)
project(CentoRTProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(figcone
    GIT_REPOSITORY https://github.com/kamchatka-volcano/figcone.git
    GIT_TAG master
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    figcone)
FetchContent_MakeAvailable(figcone)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CentoB)
