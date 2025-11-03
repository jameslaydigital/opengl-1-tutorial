/* Chapter 11: Display Lists */
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

static GLuint sphere_list;
static float rotation = 0.0f;

void create_display_lists(void) {
    sphere_list = glGenLists(1);
    glNewList(sphere_list, GL_COMPILE);
        glutSolidSphere(0.5, 32, 32);
    glEndList();
}

void init_gl(void) {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    create_display_lists();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 3, 10, 0, 0, 0, 0, 1, 0);
    
    GLfloat light_pos[] = {5, 5, 5, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    for (int i = 0; i < 20; i++) {
        glPushMatrix();
        float angle = i * 18.0f + rotation;
        float x = 3.0f * cosf(angle * 0.017453f);
        float z = 3.0f * sinf(angle * 0.017453f);
        glTranslatef(x, 0, z);
        glColor3f((float)i/20, 1.0f - (float)i/20, 0.5f);
        glCallList(sphere_list);
        glPopMatrix();
    }
    
    glutSwapBuffers();
}

void idle(void) {
    rotation += 0.5f;
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
    if (key == 27 || key == 'q') {
        glDeleteLists(sphere_list, 1);
        exit(0);
    }
}

int main(int argc, char** argv) {
    printf("Chapter 11: Display Lists\n20 spheres rendered using display lists\n");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Chapter 11: Display Lists");
    init_gl();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

