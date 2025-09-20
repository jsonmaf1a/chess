cmake_minimum_required(VERSION 3.28)
project(Chess LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
    Wisp
    GIT_REPOSITORY https://github.com/jsonmaf1a/wisp.git
    GIT_TAG main
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(Wisp)

file(GLOB_RECURSE CHESS_SOURCES src/*.cpp)
add_executable(chess ${CHESS_SOURCES})

add_custom_command(TARGET chess POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
)

target_compile_features(chess PRIVATE cxx_std_23)
target_link_libraries(chess PRIVATE SFML::Window SFML::Graphics SFML::System SFML::Audio SFML::Network Wisp)
