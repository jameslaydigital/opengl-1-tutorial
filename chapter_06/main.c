/*
 * Chapter 6: Coordinate Systems & Matrix Stacks
 * 
 * Demonstrates transformations, projections, and the matrix stack.
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "camera.h"

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 700

static int demo_mode = 0;
static float rotation = 0.0f;
static camera_t camera;
static int use_perspective = 1;

void draw_cube(float size) {
    float h = size / 2;
    
    glBegin(GL_QUADS);
    /* Front face */
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-h, -h,  h);
    glVertex3f( h, -h,  h);
    glVertex3f( h,  h,  h);
    glVertex3f(-h,  h,  h);
    
    /* Back face */
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-h, -h, -h);
    glVertex3f(-h,  h, -h);
    glVertex3f( h,  h, -h);
    glVertex3f( h, -h, -h);
    
    /* Top face */
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-h,  h, -h);
    glVertex3f(-h,  h,  h);
    glVertex3f( h,  h,  h);
    glVertex3f( h,  h, -h);
    
    /* Bottom face */
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-h, -h, -h);
    glVertex3f( h, -h, -h);
    glVertex3f( h, -h,  h);
    glVertex3f(-h, -h,  h);
    
    /* Right face */
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f( h, -h, -h);
    glVertex3f( h,  h, -h);
    glVertex3f( h,  h,  h);
    glVertex3f( h, -h,  h);
    
    /* Left face */
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-h, -h, -h);
    glVertex3f(-h, -h,  h);
    glVertex3f(-h,  h,  h);
    glVertex3f(-h,  h, -h);
    glEnd();
}

void demo_basic_transforms(void) {
    /* Translate */
    glPushMatrix();
        glTranslatef(-3.0f, 2.0f, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glutWireCube(1.0);
    glPopMatrix();
    
    /* Rotate */
    glPushMatrix();
        glTranslatef(0.0f, 2.0f, 0.0f);
        glRotatef(rotation, 0.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glutWireCube(1.0);
    glPopMatrix();
    
    /* Scale */
    glPushMatrix();
        glTranslatef(3.0f, 2.0f, 0.0f);
        float scale = 0.5f + 0.5f * sinf(rotation * 0.05f);
        glScalef(scale, scale, scale);
        glColor3f(0.0f, 0.0f, 1.0f);
        glutWireCube(1.0);
    glPopMatrix();
    
    /* Combined */
    glPushMatrix();
        glTranslatef(0.0f, -2.0f, 0.0f);
        glRotatef(rotation * 2, 0.0f, 1.0f, 0.0f);
        glTranslatef(2.0f, 0.0f, 0.0f);
        glRotatef(rotation * 3, 1.0f, 0.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glutWireCube(0.8);
    glPopMatrix();
}

void demo_hierarchy(void) {
    /* Sun */
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f);
        glRotatef(rotation * 0.5f, 0.0f, 1.0f, 0.0f);
        glutWireSphere(0.8, 16, 16);
        
        /* Earth */
        glPushMatrix();
            glRotatef(rotation, 0.0f, 1.0f, 0.0f);
            glTranslatef(3.0f, 0.0f, 0.0f);
            glColor3f(0.0f, 0.5f, 1.0f);
            glutWireSphere(0.4, 12, 12);
            
            /* Moon */
            glPushMatrix();
                glRotatef(rotation * 3, 0.0f, 1.0f, 0.0f);
                glTranslatef(0.8f, 0.0f, 0.0f);
                glColor3f(0.7f, 0.7f, 0.7f);
                glutWireSphere(0.15, 8, 8);
            glPopMatrix();
        glPopMatrix();
        
        /* Mars */
        glPushMatrix();
            glRotatef(rotation * 0.7f, 0.0f, 1.0f, 0.0f);
            glTranslatef(5.0f, 0.0f, 0.0f);
            glColor3f(1.0f, 0.3f, 0.0f);
            glutWireSphere(0.3, 12, 12);
        glPopMatrix();
    glPopMatrix();
}

void demo_cubes_grid(void) {
    int grid = 5;
    float spacing = 2.0f;
    float offset = (grid - 1) * spacing / 2.0f;
    
    for (int i = 0; i < grid; i++) {
        for (int j = 0; j < grid; j++) {
            for (int k = 0; k < grid; k++) {
                glPushMatrix();
                    float x = i * spacing - offset;
                    float y = j * spacing - offset;
                    float z = k * spacing - offset;
                    glTranslatef(x, y, z);
                    
                    float phase = (i + j + k) * 0.3f;
                    glRotatef(rotation + phase * 50, 1.0f, 1.0f, 0.0f);
                    
                    float r = (float)i / grid;
                    float g = (float)j / grid;
                    float b = (float)k / grid;
                    glColor3f(r, g, b);
                    
                    glutWireCube(0.5);
                glPopMatrix();
            }
        }
    }
}

void demo_spinning_cube(void) {
    glPushMatrix();
        glRotatef(rotation, 1.0f, 1.0f, 1.0f);
        draw_cube(2.0);
    glPopMatrix();
}

void demo_order_matters(void) {
    /* Left: Translate then Rotate */
    glPushMatrix();
        glTranslatef(-3.0f, 0.0f, 0.0f);
        glRotatef(rotation, 0.0f, 0.0f, 1.0f);
        glTranslatef(2.0f, 0.0f, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glutSolidCube(0.5);
    glPopMatrix();
    
    /* Right: Rotate then Translate */
    glPushMatrix();
        glTranslatef(3.0f, 0.0f, 0.0f);
        glTranslatef(2.0f, 0.0f, 0.0f);
        glRotatef(rotation, 0.0f, 0.0f, 1.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glutSolidCube(0.5);
    glPopMatrix();
    
    /* Draw axes for reference */
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-5.0f, 0.0f, 0.0f);
        glVertex3f(5.0f, 0.0f, 0.0f);
        
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, -5.0f, 0.0f);
        glVertex3f(0.0f, 5.0f, 0.0f);
        
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, -5.0f);
        glVertex3f(0.0f, 0.0f, 5.0f);
    glEnd();
}

void init_gl(void) {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    
    camera_init(&camera);
    camera.distance = 15.0f;
}

void setup_projection(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aspect = (float)width / height;
    if (use_perspective) {
        gluPerspective(45.0, aspect, 0.1, 100.0);
    } else {
        float size = 8.0f;
        if (width >= height) {
            glOrtho(-size * aspect, size * aspect, -size, size, 0.1, 100.0);
        } else {
            glOrtho(-size, size, -size / aspect, size / aspect, 0.1, 100.0);
        }
    }
    
    glMatrixMode(GL_MODELVIEW);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    camera_apply(&camera);
    
    switch (demo_mode) {
        case 0: demo_basic_transforms(); break;
        case 1: demo_hierarchy(); break;
        case 2: demo_cubes_grid(); break;
        case 3: demo_spinning_cube(); break;
        case 4: demo_order_matters(); break;
    }
    
    glutSwapBuffers();
}

void idle(void) {
    rotation += 0.5f;
    if (rotation >= 360.0f) rotation -= 360.0f;
    glutPostRedisplay();
}

void reshape(int w, int h) {
    setup_projection(w, h);
}

void keyboard(unsigned char key, int x, int y) {
    (void)x; (void)y;
    
    switch (key) {
        case 27: case 'q': case 'Q': exit(0); break;
        case '0': case '1': case '2': case '3': case '4':
            demo_mode = key - '0';
            printf("Demo mode: %d\n", demo_mode);
            break;
        case 'p': case 'P':
            use_perspective = !use_perspective;
            printf("%s projection\n", use_perspective ? "Perspective" : "Orthographic");
            reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            break;
        case 'w': case 'W': camera.distance -= 1.0f; break;
        case 's': case 'S': camera.distance += 1.0f; break;
    }
}

void special(int key, int x, int y) {
    (void)x; (void)y;
    switch (key) {
        case GLUT_KEY_LEFT: camera.angle_h -= 5.0f; break;
        case GLUT_KEY_RIGHT: camera.angle_h += 5.0f; break;
        case GLUT_KEY_UP: camera.angle_v += 5.0f; break;
        case GLUT_KEY_DOWN: camera.angle_v -= 5.0f; break;
    }
}

int main(int argc, char** argv) {
    printf("Chapter 6: Coordinate Systems & Matrix Stacks\n");
    printf("==============================================\n");
    printf("Demo modes:\n");
    printf("  0 - Basic transforms (translate, rotate, scale)\n");
    printf("  1 - Hierarchy (solar system)\n");
    printf("  2 - Grid of cubes\n");
    printf("  3 - Spinning cube\n");
    printf("  4 - Transform order demonstration\n");
    printf("\nControls:\n");
    printf("  0-4: Switch demo\n");
    printf("  P: Toggle perspective/orthographic\n");
    printf("  W/S: Zoom in/out\n");
    printf("  Arrows: Rotate camera\n");
    printf("  ESC/Q: Quit\n\n");
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Chapter 6: Coordinate Systems & Matrix Stacks");
    
    init_gl();
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    
    glutMainLoop();
    return 0;
}

