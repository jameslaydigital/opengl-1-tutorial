/*
 * Chapter 3: Project Skeleton
 * 
 * Entry point demonstrating a structured multi-file project.
 */

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "render.h"
#include "gl_utils.h"

/* Window dimensions */
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE  "Chapter 3: Project Skeleton"

/*
 * display_callback - GLUT display callback
 */
static void display_callback(void) {
    render_scene();
    glutSwapBuffers();
    check_gl_error("display_callback");
}

/*
 * reshape_callback - GLUT reshape callback
 */
static void reshape_callback(int width, int height) {
    glViewport(0, 0, width, height);
    printf("Window resized to %dx%d\n", width, height);
}

/*
 * keyboard_callback - GLUT keyboard callback
 */
static void keyboard_callback(unsigned char key, int x, int y) {
    (void)x;  /* Unused */
    (void)y;  /* Unused */
    
    switch (key) {
        case 27:  /* ESC */
        case 'q':
        case 'Q':
            printf("Exiting...\n");
            exit(0);
            break;
            
        default:
            printf("Key pressed: '%c' (0x%02x)\n", key, key);
            break;
    }
}

/*
 * main - Entry point
 */
int main(int argc, char** argv) {
    printf("Chapter 3: Project Skeleton\n");
    printf("============================\n");
    printf("This example demonstrates a structured multi-file project.\n");
    printf("Press ESC or 'q' to quit.\n\n");
    
    /* Initialize GLUT */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_TITLE);
    
    /* Print system info */
    print_gl_info();
    
    /* Initialize OpenGL state */
    init_render();
    
    /* Register callbacks */
    glutDisplayFunc(display_callback);
    glutIdleFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutKeyboardFunc(keyboard_callback);
    
    /* Enter main loop */
    glutMainLoop();
    
    return 0;
}

