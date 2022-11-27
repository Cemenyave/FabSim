set(gald_SOURCES src/glad.c)
add_library(glad ${gald_SOURCES})
target_include_directories(glad PUBLIC include)

