#third party includes and libs
set(GLFW_INCLUE_DIR ${THIRD_PARTY_DIR}GLFW/glfw-3.3.8.bin.WIN64/include)
set(GLFW_LIB ${THIRD_PARTY_DIR}GLFW/glfw-3.3.8.bin.WIN64/lib-vc2022/glfw3.lib)
set(GLM_INCLUDE ${THIRD_PARTY_DIR}glm-0.9.9.8)

add_library(GLFW STATIC IMPORTED)

find_package(OpenGL REQUIRED)

set(SOURCE_FILES
  main.cpp
  shader.cpp
  mesh.cpp
  camera.cpp
  object.cpp
  shapes/cube.cpp
  shapes/triangle.cpp
)

add_executable(fabric_simulator ${SOURCE_FILES})
set_property(TARGET fabric_simulator PROPERTY CXX_STANDARD 20)

target_include_directories(fabric_simulator
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(fabric_simulator
  ${OPENGL_LIBRARY}
  ${GLFW_LIB}
  glad)

target_include_directories(fabric_simulator
  PUBLIC
  ${GLFW_INCLUE_DIR}
  ${GLM_INCLUDE})

if (MSVC)
  target_link_options(fabric_simulator PUBLIC "LINKER:/NODEFAULTLIB:MSVCRT")
endif()
