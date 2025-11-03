/*
 * Chapter 7: Depth, Culling, and Viewport
 * 
 * Demonstrates depth testing, backface culling, and viewport management.
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 700

static int demo_mode = 0;
static float rotation = 0.0f;
static int depth_test_enabled = 1;
static int culling_enabled = 0;
static int wireframe = 0;

void draw_colored_cube(float x, float y, float z, float size) {
    float h = size / 2;
    
    glPushMatrix();
    glTranslatef(x, y, z);
    
    glBegin(GL_QUADS);
    /* Front face - Red */
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-h, -h,  h);
    glVertex3f( h, -h,  h);
    glVertex3f( h,  h,  h);
    glVertex3f(-h,  h,  h);
    
    /* Back face - Green */
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-h, -h, -h);
    glVertex3f(-h,  h, -h);
    glVertex3f( h,  h, -h);
    glVertex3f( h, -h, -h);
    
    /* Top face - Blue */
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-h,  h, -h);
    glVertex3f(-h,  h,  h);
    glVertex3f( h,  h,  h);
    glVertex3f( h,  h, -h);
    
    /* Bottom face - Yellow */
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-h, -h, -h);
    glVertex3f( h, -h, -h);
    glVertex3f( h, -h,  h);
    glVertex3f(-h, -h,  h);
    
    /* Right face - Magenta */
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f( h, -h, -h);
    glVertex3f( h,  h, -h);
    glVertex3f( h,  h,  h);
    glVertex3f( h, -h,  h);
    
    /* Left face - Cyan */
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-h, -h, -h);
    glVertex3f(-h, -h,  h);
    glVertex3f(-h,  h,  h);
    glVertex3f(-h,  h, -h);
    glEnd();
    
    glPopMatrix();
}

void demo_depth_test(void) {
    /* Two overlapping cubes */
    glPushMatrix();
        glTranslatef(-1.5f, 0.0f, 0.0f);
        glRotatef(rotation, 1.0f, 1.0f, 0.0f);
        draw_colored_cube(0, 0, 0, 1.5);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(1.5f, 0.0f, -2.0f);
        glRotatef(-rotation, 1.0f, 1.0f, 0.0f);
        draw_colored_cube(0, 0, 0, 1.5);
    glPopMatrix();
}

void demo_culling(void) {
    glPushMatrix();
        glRotatef(rotation, 0.0f, 1.0f, 0.0f);
        draw_colored_cube(0, 0, 0, 2.0);
    glPopMatrix();
}

void demo_split_view(void) {
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    
    /* Top-left: Front view */
    glViewport(0, h/2, w/2, h/2);
    glLoadIdentity();
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
    glPushMatrix();
        glRotatef(rotation, 0, 1, 0);
        draw_colored_cube(0, 0, 0, 2.0);
    glPopMatrix();
    
    /* Top-right: Top view */
    glViewport(w/2, h/2, w/2, h/2);
    glLoadIdentity();
    gluLookAt(0, 10, 0, 0, 0, 0, 0, 0, -1);
    glPushMatrix();
        glRotatef(rotation, 0, 1, 0);
        draw_colored_cube(0, 0, 0, 2.0);
    glPopMatrix();
    
    /* Bottom-left: Side view */
    glViewport(0, 0, w/2, h/2);
    glLoadIdentity();
    gluLookAt(10, 0, 0, 0, 0, 0, 0, 1, 0);
    glPushMatrix();
        glRotatef(rotation, 0, 1, 0);
        draw_colored_cube(0, 0, 0, 2.0);
    glPopMatrix();
    
    /* Bottom-right: Perspective */
    glViewport(w/2, 0, w/2, h/2);
    glLoadIdentity();
    gluLookAt(7, 5, 7, 0, 0, 0, 0, 1, 0);
    glPushMatrix();
        glRotatef(rotation, 0, 1, 0);
        draw_colored_cube(0, 0, 0, 2.0);
    glPopMatrix();
    
    /* Restore full viewport */
    glViewport(0, 0, w, h);
}

void demo_z_fighting(void) {
    /* Two planes at almost the same depth */
    glPushMatrix();
        glTranslatef(0, 0, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(-2, -2, 0);
            glVertex3f( 2, -2, 0);
            glVertex3f( 2,  2, 0);
            glVertex3f(-2,  2, 0);
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, 0, 0.001f);  /* Very small offset */
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(-1.5, -1.5, 0);
            glVertex3f( 1.5, -1.5, 0);
            glVertex3f( 1.5,  1.5, 0);
            glVertex3f(-1.5,  1.5, 0);
        glEnd();
    glPopMatrix();
}

void init_gl(void) {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
}

void setup_projection(void) {
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Apply settings */
    if (depth_test_enabled) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
    
    if (culling_enabled) {
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }
    
    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    if (demo_mode != 2) {
        glLoadIdentity();
        gluLookAt(0, 3, 8, 0, 0, 0, 0, 1, 0);
    }
    
    switch (demo_mode) {
        case 0: demo_depth_test(); break;
        case 1: demo_culling(); break;
        case 2: demo_split_view(); break;
        case 3: demo_z_fighting(); break;
    }
    
    glutSwapBuffers();
}

void idle(void) {
    rotation += 0.5f;
    if (rotation >= 360.0f) rotation -= 360.0f;
    glutPostRedisplay();
}

void reshape(int w, int h) {
    setup_projection();
}

void keyboard(unsigned char key, int x, int y) {
    (void)x; (void)y;
    
    switch (key) {
        case 27: case 'q': case 'Q':
            exit(0);
            break;
        case '0': case '1': case '2': case '3':
            demo_mode = key - '0';
            printf("Demo mode: %d\n", demo_mode);
            break;
        case 'd': case 'D':
            depth_test_enabled = !depth_test_enabled;
            printf("Depth test: %s\n", depth_test_enabled ? "ON" : "OFF");
            break;
        case 'c': case 'C':
            culling_enabled = !culling_enabled;
            printf("Culling: %s\n", culling_enabled ? "ON" : "OFF");
            break;
        case 'w': case 'W':
            wireframe = !wireframe;
            printf("Wireframe: %s\n", wireframe ? "ON" : "OFF");
            break;
    }
}

void print_status(void) {
    printf("\nCurrent settings:\n");
    printf("  Demo mode: %d\n", demo_mode);
    printf("  Depth test: %s\n", depth_test_enabled ? "ON" : "OFF");
    printf("  Culling: %s\n", culling_enabled ? "ON" : "OFF");
    printf("  Wireframe: %s\n", wireframe ? "ON" : "OFF");
}

int main(int argc, char** argv) {
    printf("Chapter 7: Depth, Culling, and Viewport\n");
    printf("========================================\n");
    printf("Demo modes:\n");
    printf("  0 - Depth test demonstration\n");
    printf("  1 - Backface culling\n");
    printf("  2 - Split-screen viewports\n");
    printf("  3 - Z-fighting\n");
    printf("\nControls:\n");
    printf("  0-3: Switch demo mode\n");
    printf("  D: Toggle depth testing\n");
    printf("  C: Toggle culling\n");
    printf("  W: Toggle wireframe\n");
    printf("  ESC/Q: Quit\n");
    
    print_status();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Chapter 7: Depth, Culling, and Viewport");
    
    init_gl();
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}

