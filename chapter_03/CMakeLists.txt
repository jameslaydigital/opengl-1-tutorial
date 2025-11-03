cmake_minimum_required(VERSION 3.10)
project(Chapter03_ProjectSkeleton C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add compile options
add_compile_options(-Wall -Wextra -pedantic)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Source files
set(SOURCES
    main.c
    render.c
    gl_utils.c
)

# Header files (for IDE integration)
set(HEADERS
    render.h
    gl_utils.h
)

# Add executable
add_executable(demo ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(demo 
    ${OPENGL_LIBRARIES} 
    ${GLUT_LIBRARIES}
)

# Include directories
target_include_directories(demo PRIVATE 
    ${OPENGL_INCLUDE_DIR} 
    ${GLUT_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# macOS: Suppress deprecation warnings
if(APPLE)
    target_compile_options(demo PRIVATE -Wno-deprecated-declarations)
endif()

# Add math library on Unix
if(UNIX AND NOT APPLE)
    target_link_libraries(demo m)
endif()

# Set output directory
set_target_properties(demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Debug configuration
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -DDEBUG")

# Release configuration
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -DNDEBUG")

# Print build info
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "OpenGL: ${OPENGL_LIBRARIES}")
message(STATUS "GLUT: ${GLUT_LIBRARIES}")

