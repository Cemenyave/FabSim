cmake_minimum_required(VERSION 3.16)

project(fabric_simulator)

set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/thirdparty/)

add_subdirectory(thirdparty/glad)
add_subdirectory(source)
