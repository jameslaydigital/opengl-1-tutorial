/*
 * Chapter 19: Packaging a Demo
 * 
 * Demonstrates best practices for distributable OpenGL applications.
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

static float rotation = 0.0f;

/* Asset path handling */
char* get_asset_path(const char* asset_name) {
    static char path[512];
    
    /* Try to find assets relative to executable */
    #ifdef _WIN32
        /* On Windows, try exe directory */
        snprintf(path, sizeof(path), "%s", asset_name);
    #else
        /* On Unix, try current directory, then ./assets/ */
        snprintf(path, sizeof(path), "%s", asset_name);
    #endif
    
    return path;
}

void print_packaging_info(void) {
    printf("\n=== Packaging Information ===\n");
    printf("Application: OpenGL Demo\n");
    printf("Version: 1.0.0\n");
    
    #ifdef _WIN32
        printf("Platform: Windows\n");
        printf("Required DLLs:\n");
        printf("  - freeglut.dll (if dynamically linked)\n");
        printf("  - msvcr*.dll (Visual C++ runtime)\n");
        printf("\nDistribution:\n");
        printf("  1. Include all DLLs in same directory as .exe\n");
        printf("  2. Test on clean Windows install\n");
    #elif __APPLE__
        printf("Platform: macOS\n");
        printf("Distribution:\n");
        printf("  1. Create .app bundle\n");
        printf("  2. Include frameworks in bundle\n");
        printf("  3. Code sign for distribution\n");
        printf("\n⚠ Note: OpenGL deprecated on macOS\n");
    #elif __linux__
        printf("Platform: Linux\n");
        printf("Required libraries:\n");
        printf("  - libGL.so.1\n");
        printf("  - libGLU.so.1\n");
        printf("  - libglut.so.3 (or freeglut3)\n");
        printf("\nDistribution:\n");
        printf("  1. Static linking (larger but self-contained)\n");
        printf("  2. Dynamic linking (smaller, requires deps)\n");
        printf("  3. AppImage for portable distribution\n");
    #endif
    
    printf("\n=== Build Information ===\n");
    printf("Compiled: %s %s\n", __DATE__, __TIME__);
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("GLUT Version: ");
    #ifdef GLUT_API_VERSION
        printf("%d\n", GLUT_API_VERSION);
    #else
        printf("Unknown\n");
    #endif
    
    printf("\n=== Asset Management ===\n");
    printf("Assets should be placed relative to executable:\n");
    printf("  ./textures/   - Texture files\n");
    printf("  ./models/     - 3D model files\n");
    printf("  ./shaders/    - Shader files (modern GL)\n");
    printf("\n");
}

void init_gl(void) {
    glClearColor(0.15f, 0.15f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    GLfloat light_pos[] = {5, 5, 5, 1};
    GLfloat light_ambient[] = {0.3f, 0.3f, 0.3f, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 3, 8, 0, 0, 0, 0, 1, 0);
    
    GLfloat light_pos[] = {5, 5, 5, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    /* Draw demo scene */
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef((i-1)*2.5f, 0, 0);
        glRotatef(rotation + i*30, 0, 1, 0);
        
        float hue = i / 3.0f;
        glColor3f(1.0f-hue, hue, 0.5f);
        
        if (i == 0) glutSolidCube(1.5);
        else if (i == 1) glutSolidSphere(0.8, 20, 20);
        else glutSolidTeapot(0.8);
        
        glPopMatrix();
    }
    
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
    if (key == 'i' || key == 'I') print_packaging_info();
}

int main(int argc, char** argv) {
    printf("Chapter 19: Packaging a Demo\n");
    printf("=============================\n");
    printf("This demo shows best practices for distributable applications\n");
    printf("Press 'I' for packaging information\n");
    printf("Press ESC or 'Q' to quit\n\n");
    
    print_packaging_info();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 600);
    glutCreateWindow("Chapter 19: Packaging Demo");
    
    init_gl();
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}

