/*
 * gl_utils.c - OpenGL utility implementations
 */

#include <GL/glut.h>
#include <stdio.h>
#include "gl_utils.h"

/*
 * check_gl_error - Check for OpenGL errors and print them
 */
void check_gl_error(const char* context) {
    GLenum err;
    int error_count = 0;
    
    while ((err = glGetError()) != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error in %s: 0x%x\n", context, err);
        error_count++;
    }
    
    if (error_count > 0) {
        fprintf(stderr, "Total errors in %s: %d\n", context, error_count);
    }
}

/*
 * print_gl_info - Print OpenGL version and driver information
 */
void print_gl_info(void) {
    const char* version = (const char*)glGetString(GL_VERSION);
    const char* vendor = (const char*)glGetString(GL_VENDOR);
    const char* renderer = (const char*)glGetString(GL_RENDERER);
    
    printf("OpenGL Information:\n");
    printf("  Version:  %s\n", version ? version : "Unknown");
    printf("  Vendor:   %s\n", vendor ? vendor : "Unknown");
    printf("  Renderer: %s\n", renderer ? renderer : "Unknown");
    printf("\n");
}

