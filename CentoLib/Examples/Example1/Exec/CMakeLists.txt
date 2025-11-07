cmake_minimum_required(VERSION 3.28)

add_executable(Exec src/main.cpp)
target_link_libraries(Exec
    PRIVATE
        CentoLib
)

set_target_properties(Exec PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Example1
)

target_compile_features(Exec PUBLIC cxx_std_20)

add_custom_command(
    TARGET Exec POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:CentoRT>
        ${EXAMPLE1_RUNTIME_DIR}/
)