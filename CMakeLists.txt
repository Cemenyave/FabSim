cmake_minimum_required(VERSION 3.16)

project(fabric_simulator)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/thirdparty/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)

add_subdirectory(thirdparty/glad)
add_subdirectory(source)
