/*
 * Chapter 21: Where to Go Next
 * 
 * A comprehensive demo combining techniques from all chapters.
 * This serves as a "graduation" project showing mastery of OpenGL 1.1.
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* Camera state */
static struct {
    float distance;
    float angle_h;
    float angle_v;
} camera = {15.0f, 45.0f, 30.0f};

static float rotation = 0.0f;
static int show_info = 1;
static int wireframe = 0;
static int lighting_enabled = 1;
static int fog_enabled = 0;

/* Materials */
void set_material_gold(void) {
    GLfloat mat_ambient[] = {0.24725f, 0.1995f, 0.0745f, 1.0f};
    GLfloat mat_diffuse[] = {0.75164f, 0.60648f, 0.22648f, 1.0f};
    GLfloat mat_specular[] = {0.628281f, 0.555802f, 0.366065f, 1.0f};
    GLfloat mat_shininess = 51.2f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}

void set_material_emerald(void) {
    GLfloat mat_ambient[] = {0.0215f, 0.1745f, 0.0215f, 1.0f};
    GLfloat mat_diffuse[] = {0.07568f, 0.61424f, 0.07568f, 1.0f};
    GLfloat mat_specular[] = {0.633f, 0.727811f, 0.633f, 1.0f};
    GLfloat mat_shininess = 76.8f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}

void draw_text_2d(int x, int y, const char* text) {
    glRasterPos2i(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}

void draw_hud(void) {
    if (!show_info) return;
    
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    
    /* Semi-transparent background */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2i(10, height-120);
        glVertex2i(300, height-120);
        glVertex2i(300, height-10);
        glVertex2i(10, height-10);
    glEnd();
    glDisable(GL_BLEND);
    
    /* Text */
    glColor3f(1.0f, 1.0f, 1.0f);
    draw_text_2d(20, height-25, "OpenGL 1.1 Tutorial Complete!");
    draw_text_2d(20, height-45, "Techniques Demonstrated:");
    draw_text_2d(20, height-65, "  Transformations & Camera");
    draw_text_2d(20, height-80, "  Lighting & Materials");
    draw_text_2d(20, height-95, "  Depth Testing & Culling");
    draw_text_2d(20, height-110, "  Text Rendering");
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_DEPTH_TEST);
    if (lighting_enabled) glEnable(GL_LIGHTING);
}

void setup_scene(void) {
    /* Lighting setup */
    GLfloat light_pos[] = {5, 8, 5, 1};
    GLfloat light_ambient[] = {0.3f, 0.3f, 0.3f, 1};
    GLfloat light_diffuse[] = {1, 1, 1, 1};
    GLfloat light_specular[] = {1, 1, 1, 1};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    /* Second light */
    GLfloat light1_pos[] = {-5, 3, -5, 1};
    GLfloat light1_diffuse[] = {0.3f, 0.3f, 0.5f, 1};
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
}

void draw_ground(void) {
    glDisable(GL_LIGHTING);
    glColor3f(0.3f, 0.3f, 0.4f);
    glBegin(GL_LINES);
    for (int i = -10; i <= 10; i++) {
        glVertex3f(i, 0, -10);
        glVertex3f(i, 0, 10);
        glVertex3f(-10, 0, i);
        glVertex3f(10, 0, i);
    }
    glEnd();
    if (lighting_enabled) glEnable(GL_LIGHTING);
}

void draw_scene(void) {
    /* Ground grid */
    draw_ground();
    
    /* Center rotating object - Gold torus */
    glPushMatrix();
    set_material_gold();
    glRotatef(rotation, 0, 1, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(0.3, 1.0, 20, 30);
    glPopMatrix();
    
    /* Orbiting objects */
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glRotatef(rotation + i * 90, 0, 1, 0);
        glTranslatef(4.0f, 1.5f, 0);
        
        if (i % 2 == 0) {
            set_material_emerald();
            glutSolidSphere(0.5, 20, 20);
        } else {
            set_material_gold();
            glutSolidCube(0.8);
        }
        glPopMatrix();
    }
    
    /* Teapot showcase */
    glPushMatrix();
    glTranslatef(0, 3.0f, 0);
    glRotatef(-90, 1, 0, 0);
    glRotatef(rotation * 2, 0, 0, 1);
    set_material_gold();
    glutSolidTeapot(0.8);
    glPopMatrix();
}

void init_gl(void) {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);
    
    /* Fog setup */
    GLfloat fog_color[] = {0.1f, 0.1f, 0.15f, 1.0f};
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fog_color);
    glFogf(GL_FOG_START, 10.0f);
    glFogf(GL_FOG_END, 25.0f);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    /* Apply camera */
    float h_rad = camera.angle_h * 0.017453f;
    float v_rad = camera.angle_v * 0.017453f;
    float eye_x = camera.distance * cosf(v_rad) * sinf(h_rad);
    float eye_y = camera.distance * sinf(v_rad);
    float eye_z = camera.distance * cosf(v_rad) * cosf(h_rad);
    
    gluLookAt(eye_x, eye_y, eye_z, 0, 1, 0, 0, 1, 0);
    
    /* Apply settings */
    if (lighting_enabled) glEnable(GL_LIGHTING); else glDisable(GL_LIGHTING);
    if (fog_enabled) glEnable(GL_FOG); else glDisable(GL_FOG);
    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    
    /* Setup and draw scene */
    setup_scene();
    draw_scene();
    
    /* Draw HUD */
    draw_hud();
    
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
        case 'h': case 'H':
            show_info = !show_info;
            printf("HUD: %s\n", show_info ? "ON" : "OFF");
            break;
        case 'w': case 'W':
            wireframe = !wireframe;
            printf("Wireframe: %s\n", wireframe ? "ON" : "OFF");
            break;
        case 'l': case 'L':
            lighting_enabled = !lighting_enabled;
            printf("Lighting: %s\n", lighting_enabled ? "ON" : "OFF");
            break;
        case 'f': case 'F':
            fog_enabled = !fog_enabled;
            printf("Fog: %s\n", fog_enabled ? "ON" : "OFF");
            break;
    }
}

void special(int key, int x, int y) {
    (void)x; (void)y;
    switch (key) {
        case GLUT_KEY_LEFT: camera.angle_h -= 5; break;
        case GLUT_KEY_RIGHT: camera.angle_h += 5; break;
        case GLUT_KEY_UP: camera.angle_v += 5; break;
        case GLUT_KEY_DOWN: camera.angle_v -= 5; break;
        case GLUT_KEY_PAGE_UP: camera.distance -= 1; break;
        case GLUT_KEY_PAGE_DOWN: camera.distance += 1; break;
    }
    if (camera.distance < 5) camera.distance = 5;
    if (camera.distance > 50) camera.distance = 50;
}

int main(int argc, char** argv) {
    printf("Chapter 21: Where to Go Next\n");
    printf("============================\n");
    printf("Comprehensive Demo - Everything We've Learned!\n\n");
    printf("This demo combines:\n");
    printf("  ✓ Hierarchical transformations\n");
    printf("  ✓ Multiple light sources\n");
    printf("  ✓ Material properties\n");
    printf("  ✓ Camera controls\n");
    printf("  ✓ Text overlay (HUD)\n");
    printf("  ✓ Fog effects\n");
    printf("  ✓ Wireframe mode\n\n");
    printf("Controls:\n");
    printf("  Arrow Keys: Rotate camera\n");
    printf("  PgUp/PgDn: Zoom\n");
    printf("  H: Toggle HUD\n");
    printf("  W: Toggle wireframe\n");
    printf("  L: Toggle lighting\n");
    printf("  F: Toggle fog\n");
    printf("  ESC/Q: Quit\n\n");
    printf("Congratulations on completing the OpenGL 1.1 tutorial!\n");
    printf("Next steps: learnopengl.com for modern OpenGL\n\n");
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Chapter 21: OpenGL 1.1 - The Complete Journey");
    
    init_gl();
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    
    glutMainLoop();
    return 0;
}

