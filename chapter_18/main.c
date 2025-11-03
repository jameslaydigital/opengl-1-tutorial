/*
 * Chapter 18: Cross-Platform Notes
 * 
 * Demonstrates cross-platform OpenGL development.
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

static float rotation = 0.0f;

void print_platform_info(void) {
    printf("\n=== Platform Information ===\n");
    
    #ifdef _WIN32
        printf("Platform: Windows\n");
        printf("Notes: WGL provides native GL context\n");
    #elif __APPLE__
        printf("Platform: macOS\n");
        printf("Notes: OpenGL deprecated since 10.14, max version 4.1\n");
        printf("       Apple recommends Metal for new development\n");
    #elif __linux__
        printf("Platform: Linux\n");
        printf("Notes: GLX provides native GL context\n");
        printf("       Excellent OpenGL support via Mesa\n");
    #else
        printf("Platform: Unknown\n");
    #endif
    
    printf("\nOpenGL Information:\n");
    printf("  Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("  Renderer: %s\n", glGetString(GL_RENDERER));
    printf("  Version:  %s\n", glGetString(GL_VERSION));
    
    #ifdef __APPLE__
        printf("\n⚠ macOS Deprecation Notice:\n");
        printf("  This code uses deprecated OpenGL API\n");
        printf("  Compiled with -Wno-deprecated-declarations\n");
        printf("  For production apps, consider Metal or MoltenVK\n");
    #endif
    
    printf("\nGLUT provides cross-platform abstraction for:\n");
    printf("  ✓ Window creation\n");
    printf("  ✓ Input handling\n");
    printf("  ✓ OpenGL context management\n");
    printf("  ✓ Event loop\n");
    printf("\n");
}

void init_gl(void) {
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    GLfloat light_pos[] = {5, 5, 5, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 3, 8, 0, 0, 0, 0, 1, 0);
    
    GLfloat light_pos[] = {5, 5, 5, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    /* Draw platform-colored objects */
    glPushMatrix();
    glTranslatef(-2.5f, 0, 0);
    glRotatef(rotation, 0, 1, 0);
    #ifdef _WIN32
        glColor3f(0.0f, 0.5f, 1.0f); /* Windows blue */
    #elif __APPLE__
        glColor3f(0.5f, 0.5f, 0.5f); /* Apple gray */
    #elif __linux__
        glColor3f(1.0f, 0.8f, 0.0f); /* Linux gold */
    #else
        glColor3f(1.0f, 0.0f, 1.0f); /* Unknown magenta */
    #endif
    glutSolidCube(2.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2.5f, 0, 0);
    glRotatef(-rotation, 1, 1, 0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glutSolidTeapot(1.0);
    glPopMatrix();
    
    glutSwapBuffers();
}

void idle(void) {
    rotation += 0.5f;
    if (rotation >= 360.0f) rotation -= 360.0f;
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w/h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    (void)x; (void)y;
    if (key == 27 || key == 'q' || key == 'Q') exit(0);
    if (key == 'i' || key == 'I') print_platform_info();
}

int main(int argc, char** argv) {
    printf("Chapter 18: Cross-Platform Notes\n");
    printf("=================================\n");
    printf("This demo compiles and runs on Windows, Linux, and macOS\n");
    printf("Press 'I' to print platform information\n");
    printf("Press ESC or 'Q' to quit\n");
    
    print_platform_info();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Chapter 18: Cross-Platform OpenGL");
    
    init_gl();
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}

