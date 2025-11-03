cmake_minimum_required(VERSION 3.10)
project(Chapter02_HelloWindow C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLUT
find_package(GLUT REQUIRED)

# Add executable
add_executable(demo main.c)

# Link libraries
target_link_libraries(demo ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

# Include directories
target_include_directories(demo PRIVATE ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

# macOS: Suppress deprecation warnings
if(APPLE)
    target_compile_options(demo PRIVATE -Wno-deprecated-declarations)
endif()

# Set output directory
set_target_properties(demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Print build info
message(STATUS "OpenGL found: ${OPENGL_LIBRARIES}")
message(STATUS "GLUT found: ${GLUT_LIBRARIES}")

