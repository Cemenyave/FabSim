set(GLFW_INCLUE_DIR ${THIRD_PARTY_DIR}GLFW/glfw-3.3.8.bin.WIN64/include)
set(GLFW_LIB ${THIRD_PARTY_DIR}GLFW/glfw-3.3.8.bin.WIN64/lib-vc2022/glfw3.lib)

add_library(GLFW STATIC IMPORTED)

find_package(OpenGL REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(fabric_simulator ${SOURCE_FILES})

target_link_libraries(fabric_simulator ${OPENGL_LIBRARY} ${GLFW_LIB} glad)
target_include_directories(fabric_simulator PUBLIC ${GLFW_INCLUE_DIR})

if (MSVC)
  target_link_options(fabric_simulator PUBLIC "LINKER:/NODEFAULTLIB:MSVCRT")
endif()
