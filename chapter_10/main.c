/* Chapter 10: Common OpenGL State */
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

static int blend_enabled = 0;
static int fog_enabled = 0;
static float rotation = 0.0f;

void init_gl(void) {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glFogi(GL_FOG_MODE, GL_LINEAR);
    GLfloat fog_color[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glFogfv(GL_FOG_COLOR, fog_color);
    glFogf(GL_FOG_START, 3.0f);
    glFogf(GL_FOG_END, 10.0f);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 8, 0, 0, 0, 0, 1, 0);
    
    if (blend_enabled) glEnable(GL_BLEND); else glDisable(GL_BLEND);
    if (fog_enabled) glEnable(GL_FOG); else glDisable(GL_FOG);
    
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef((i-2)*1.5f, 0, -i*0.8f);
        glRotatef(rotation + i*20, 0, 1, 0);
        glColor4f(1.0f, 0.3f * i, 0.7f - 0.1f * i, blend_enabled ? 0.6f : 1.0f);
        glutSolidCube(1.0);
        glPopMatrix();
    }
    
    glutSwapBuffers();
}

void idle(void) {
    rotation += 0.5f;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    (void)x; (void)y;
    if (key == 27 || key == 'q') exit(0);
    if (key == 'b') { blend_enabled = !blend_enabled; printf("Blend: %s\n", blend_enabled?"ON":"OFF"); }
    if (key == 'f') { fog_enabled = !fog_enabled; printf("Fog: %s\n", fog_enabled?"ON":"OFF"); }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w/h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    printf("Chapter 10: Blending and Fog\nB: Toggle blending\nF: Toggle fog\n");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Chapter 10");
    init_gl();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

