/*
 * Chapter 15: Common Pitfalls
 * 
 * Demonstrates common OpenGL problems and their solutions.
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int demo_mode = 0;
static float rotation = 0.0f;
static int lighting_enabled = 1;
static int normals_enabled = 1;
static int normalize_enabled = 1;

/* Draw cube with optional normals */
void draw_cube_with_normals(float size) {
    float h = size / 2;
    
    glBegin(GL_QUADS);
    
    /* Front face */
    if (normals_enabled) glNormal3f(0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-h, -h,  h);
    glVertex3f( h, -h,  h);
    glVertex3f( h,  h,  h);
    glVertex3f(-h,  h,  h);
    
    /* Back face */
    if (normals_enabled) glNormal3f(0.0f, 0.0f, -1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-h, -h, -h);
    glVertex3f(-h,  h, -h);
    glVertex3f( h,  h, -h);
    glVertex3f( h, -h, -h);
    
    /* Top face */
    if (normals_enabled) glNormal3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-h,  h, -h);
    glVertex3f(-h,  h,  h);
    glVertex3f( h,  h,  h);
    glVertex3f( h,  h, -h);
    
    /* Bottom face */
    if (normals_enabled) glNormal3f(0.0f, -1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-h, -h, -h);
    glVertex3f( h, -h, -h);
    glVertex3f( h, -h,  h);
    glVertex3f(-h, -h,  h);
    
    /* Right face */
    if (normals_enabled) glNormal3f(1.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f( h, -h, -h);
    glVertex3f( h,  h, -h);
    glVertex3f( h,  h,  h);
    glVertex3f( h, -h,  h);
    
    /* Left face */
    if (normals_enabled) glNormal3f(-1.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-h, -h, -h);
    glVertex3f(-h, -h,  h);
    glVertex3f(-h,  h,  h);
    glVertex3f(-h,  h, -h);
    
    glEnd();
}

/* Demo 0: Lighting without normals */
void demo_missing_normals(void) {
    glPushMatrix();
    glTranslatef(-2.5f, 0, 0);
    glRotatef(rotation, 1, 1, 0);
    normals_enabled = 0;
    draw_cube_with_normals(1.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2.5f, 0, 0);
    glRotatef(rotation, 1, 1, 0);
    normals_enabled = 1;
    draw_cube_with_normals(1.5);
    glPopMatrix();
}

/* Demo 1: Z-fighting */
void demo_z_fighting(void) {
    /* Two planes at nearly the same depth */
    glDisable(GL_LIGHTING);
    
    /* Red plane */
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-2, -2, 0.000f);
        glVertex3f( 2, -2, 0.000f);
        glVertex3f( 2,  2, 0.000f);
        glVertex3f(-2,  2, 0.000f);
    glEnd();
    
    /* Green plane - very slightly in front */
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-1.5, -1.5, 0.001f);
        glVertex3f( 1.5, -1.5, 0.001f);
        glVertex3f( 1.5,  1.5, 0.001f);
        glVertex3f(-1.5,  1.5, 0.001f);
    glEnd();
    
    if (lighting_enabled) glEnable(GL_LIGHTING);
}

/* Demo 2: Scaled normals */
void demo_scaled_normals(void) {
    glPushMatrix();
    glTranslatef(-3.0f, 0, 0);
    glScalef(2.0f, 0.5f, 1.0f);
    if (!normalize_enabled) glDisable(GL_NORMALIZE);
    draw_cube_with_normals(1.0);
    if (!normalize_enabled) glEnable(GL_NORMALIZE);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(3.0f, 0, 0);
    glScalef(2.0f, 0.5f, 1.0f);
    draw_cube_with_normals(1.0);
    glPopMatrix();
}

/* Demo 3: Wrong winding order */
void demo_winding_order(void) {
    glEnable(GL_CULL_FACE);
    
    /* Correct winding (CCW) */
    glPushMatrix();
    glTranslatef(-2.0f, 0, 0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-1, -1, 0);
        glVertex3f( 1, -1, 0);
        glVertex3f( 1,  1, 0);
        glVertex3f(-1,  1, 0);
    glEnd();
    glPopMatrix();
    
    /* Wrong winding (CW - culled!) */
    glPushMatrix();
    glTranslatef(2.0f, 0, 0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-1, -1, 0);
        glVertex3f(-1,  1, 0);
        glVertex3f( 1,  1, 0);
        glVertex3f( 1, -1, 0);
    glEnd();
    glPopMatrix();
    
    glDisable(GL_CULL_FACE);
}

void setup_lighting(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    GLfloat light_pos[] = {5, 5, 5, 1};
    GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1};
    GLfloat light_diffuse[] = {1, 1, 1, 1};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
}

void init_gl(void) {
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    setup_lighting();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 3, 8, 0, 0, 0, 0, 1, 0);
    
    if (lighting_enabled) glEnable(GL_LIGHTING); else glDisable(GL_LIGHTING);
    
    GLfloat light_pos[] = {5, 5, 5, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    switch (demo_mode) {
        case 0: demo_missing_normals(); break;
        case 1: demo_z_fighting(); break;
        case 2: demo_scaled_normals(); break;
        case 3: demo_winding_order(); break;
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
    
    switch (key) {
        case 27: case 'q': case 'Q': exit(0); break;
        case '0': case '1': case '2': case '3':
            demo_mode = key - '0';
            printf("Demo: %d\n", demo_mode);
            break;
        case 'l': case 'L':
            lighting_enabled = !lighting_enabled;
            printf("Lighting: %s\n", lighting_enabled ? "ON" : "OFF");
            break;
        case 'n': case 'N':
            normalize_enabled = !normalize_enabled;
            if (normalize_enabled) glEnable(GL_NORMALIZE);
            else glDisable(GL_NORMALIZE);
            printf("Normalize: %s\n", normalize_enabled ? "ON" : "OFF");
            break;
    }
}

int main(int argc, char** argv) {
    printf("Chapter 15: Common Pitfalls\n");
    printf("===========================\n");
    printf("Demo modes:\n");
    printf("  0 - Missing normals (left: no normals, right: with normals)\n");
    printf("  1 - Z-fighting (overlapping planes)\n");
    printf("  2 - Scaled normals (left: no normalize, right: normalized)\n");
    printf("  3 - Wrong winding order (left: correct, right: culled)\n");
    printf("\nControls:\n");
    printf("  0-3: Switch demo\n");
    printf("  L: Toggle lighting\n");
    printf("  N: Toggle normalize (demo 2)\n");
    printf("  ESC/Q: Quit\n\n");
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 700);
    glutCreateWindow("Chapter 15: Common Pitfalls");
    
    init_gl();
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}

