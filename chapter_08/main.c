/*
 * Chapter 8: Lighting and Materials
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "materials.h"

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 700

static int material_preset = 0;
static int lighting_enabled = 1;
static float rotation = 0.0f;
static float light_angle = 0.0f;

void setup_lighting(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    
    /* Global ambient */
    GLfloat global_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    
    /* Light position (updated in display) */
    GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void init_gl(void) {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    setup_lighting();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(0, 3, 8, 0, 0, 0, 0, 1, 0);
    
    /* Update light position */
    float lx = 5.0f * cosf(light_angle * 0.017453f);
    float lz = 5.0f * sinf(light_angle * 0.017453f);
    GLfloat light_pos[] = {lx, 3.0f, lz, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    /* Draw light indicator */
    glPushMatrix();
        glTranslatef(lx, 3.0f, lz);
        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 1.0f, 0.0f);
        glutSolidSphere(0.2, 10, 10);
        if (lighting_enabled) glEnable(GL_LIGHTING);
    glPopMatrix();
    
    /* Apply material */
    material_apply(material_preset);
    
    /* Draw objects */
    glPushMatrix();
        glTranslatef(-2.5f, 0.0f, 0.0f);
        glRotatef(rotation, 0.0f, 1.0f, 0.0f);
        glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(rotation, 1.0f, 1.0f, 0.0f);
        glutSolidCube(1.8);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(2.5f, 0.0f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(rotation, 0.0f, 0.0f, 1.0f);
        glutSolidTorus(0.3, 0.8, 20, 30);
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
    gluPerspective(45.0, (double)w / h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    (void)x; (void)y;
    
    switch (key) {
        case 27: case 'q': case 'Q': exit(0); break;
        case 'l': case 'L':
            lighting_enabled = !lighting_enabled;
            if (lighting_enabled) glEnable(GL_LIGHTING);
            else glDisable(GL_LIGHTING);
            printf("Lighting: %s\n", lighting_enabled ? "ON" : "OFF");
            break;
        case '0': case '1': case '2': case '3':
        case '4': case '5': case '6': case '7':
            material_preset = key - '0';
            printf("Material: %s\n", material_get_name(material_preset));
            break;
    }
}

void special(int key, int x, int y) {
    (void)x; (void)y;
    switch (key) {
        case GLUT_KEY_LEFT: light_angle -= 5.0f; break;
        case GLUT_KEY_RIGHT: light_angle += 5.0f; break;
    }
}

int main(int argc, char** argv) {
    printf("Chapter 8: Lighting and Materials\n");
    printf("==================================\n");
    printf("Controls:\n");
    printf("  0-7: Switch material preset\n");
    printf("  L: Toggle lighting\n");
    printf("  Left/Right: Move light\n");
    printf("  ESC/Q: Quit\n\n");
    
    printf("Materials:\n");
    for (int i = 0; i < 8; i++) {
        printf("  %d - %s\n", i, material_get_name(i));
    }
    printf("\n");
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Chapter 8: Lighting and Materials");
    
    init_gl();
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    
    glutMainLoop();
    return 0;
}

