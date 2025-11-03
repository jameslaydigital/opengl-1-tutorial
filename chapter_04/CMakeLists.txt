cmake_minimum_required(VERSION 3.10)
project(Chapter04_GLUT101 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(demo main.c)
target_link_libraries(demo ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
target_include_directories(demo PRIVATE ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

if(APPLE)
    target_compile_options(demo PRIVATE -Wno-deprecated-declarations)
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(demo m)
endif()

