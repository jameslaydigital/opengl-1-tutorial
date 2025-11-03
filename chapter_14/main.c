/* Chapter 14: Text & UI */
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

static int fps_counter = 0;
static float fps = 0.0f;
static int last_time = 0;
static float rotation = 0.0f;

void draw_text_2d(int x, int y, const char* text, void* font) {
    glRasterPos2i(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void draw_hud(int width, int height) {
    /* Switch to 2D orthographic */
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    
    /* Draw semi-transparent panel */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2i(10, height-80);
        glVertex2i(250, height-80);
        glVertex2i(250, height-10);
        glVertex2i(10, height-10);
    glEnd();
    glDisable(GL_BLEND);
    
    /* Draw text */
    char buffer[256];
    glColor3f(1.0f, 1.0f, 1.0f);
    
    sprintf(buffer, "FPS: %.1f", fps);
    draw_text_2d(20, height-25, buffer, GLUT_BITMAP_HELVETICA_18);
    
    sprintf(buffer, "Chapter 14: Text & UI");
    draw_text_2d(20, height-50, buffer, GLUT_BITMAP_HELVETICA_12);
    
    /* Restore 3D state */
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_DEPTH_TEST);
}

void init_gl(void) {
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 3, 8, 0, 0, 0, 0, 1, 0);
    
    GLfloat light_pos[] = {5, 5, 5, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    glEnable(GL_LIGHTING);
    glPushMatrix();
    glRotatef(rotation, 0, 1, 0);
    glColor3f(0.8f, 0.3f, 0.2f);
    glutSolidTeapot(1.0);
    glPopMatrix();
    
    /* Draw HUD */
    draw_hud(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    
    /* Update FPS */
    fps_counter++;
    int current_time = glutGet(GLUT_ELAPSED_TIME);
    if (current_time - last_time > 1000) {
        fps = fps_counter * 1000.0f / (current_time - last_time);
        fps_counter = 0;
        last_time = current_time;
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
    if (key == 27 || key == 'q') exit(0);
}

int main(int argc, char** argv) {
    printf("Chapter 14: Text & UI\nFPS counter displayed in top-left corner\n");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Chapter 14: Text & UI");
    init_gl();
    last_time = glutGet(GLUT_ELAPSED_TIME);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

