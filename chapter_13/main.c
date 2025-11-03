/* Chapter 13: Input & Interaction */
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

static struct {
    float x, y, z;
    float yaw, pitch;
    int keys[256];
} camera = {0, 0, 5, 0, 20};

static int mouse_x, mouse_y, mouse_dragging = 0;

void init_gl(void) {
    glClearColor(0.3f, 0.5f, 0.7f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void update_camera(void) {
    float speed = 0.1f;
    float dx = 0, dz = 0;
    
    if (camera.keys['w']) dz -= speed;
    if (camera.keys['s']) dz += speed;
    if (camera.keys['a']) dx -= speed;
    if (camera.keys['d']) dx += speed;
    
    float yaw_rad = camera.yaw * 0.017453f;
    camera.x += dx * cosf(yaw_rad) - dz * sinf(yaw_rad);
    camera.z += dx * sinf(yaw_rad) + dz * cosf(yaw_rad);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    float yaw_rad = camera.yaw * 0.017453f;
    float pitch_rad = camera.pitch * 0.017453f;
    float cx = camera.x + sinf(yaw_rad) * cosf(pitch_rad);
    float cy = camera.y - sinf(pitch_rad);
    float cz = camera.z - cosf(yaw_rad) * cosf(pitch_rad);
    
    gluLookAt(camera.x, camera.y, camera.z, cx, cy, cz, 0, 1, 0);
    
    GLfloat light_pos[] = {5, 5, 5, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    /* Draw ground grid */
    glDisable(GL_LIGHTING);
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    for (int i = -10; i <= 10; i++) {
        glVertex3f(i, 0, -10); glVertex3f(i, 0, 10);
        glVertex3f(-10, 0, i); glVertex3f(10, 0, i);
    }
    glEnd();
    glEnable(GL_LIGHTING);
    
    /* Draw cubes */
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            glPushMatrix();
            glTranslatef(i*2-4, 0.5, j*2-4);
            glColor3f((float)i/5, (float)j/5, 0.5f);
            glutSolidCube(0.8);
            glPopMatrix();
        }
    }
    
    glutSwapBuffers();
}

void idle(void) {
    update_camera();
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w/h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    (void)x; (void)y;
    camera.keys[key] = 1;
    if (key == 27 || key == 'q') exit(0);
}

void keyboardUp(unsigned char key, int x, int y) {
    (void)x; (void)y;
    camera.keys[key] = 0;
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        mouse_dragging = (state == GLUT_DOWN);
        mouse_x = x;
        mouse_y = y;
    }
}

void motion(int x, int y) {
    if (mouse_dragging) {
        camera.yaw += (x - mouse_x) * 0.5f;
        camera.pitch += (y - mouse_y) * 0.5f;
        if (camera.pitch > 89) camera.pitch = 89;
        if (camera.pitch < -89) camera.pitch = -89;
        mouse_x = x;
        mouse_y = y;
    }
}

int main(int argc, char** argv) {
    printf("Chapter 13: Input & Interaction\n");
    printf("WASD: Move  |  Mouse drag: Look around  |  ESC: Quit\n");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 700);
    glutCreateWindow("Chapter 13: Input & Interaction");
    init_gl();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
}

