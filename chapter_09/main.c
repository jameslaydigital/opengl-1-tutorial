/*
 * Chapter 9: Textures
 * 
 * Demonstrates texture loading and mapping with procedurally generated textures.
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TEX_SIZE 256

static GLuint texture_id;
static int filter_mode = 0;
static int wrap_mode = 0;
static float rotation = 0.0f;
static float tex_scroll = 0.0f;

/* Generate checkerboard texture */
void generate_checkerboard(unsigned char* data, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int c = (((i & 16) == 0) ^ ((j & 16) == 0)) * 255;
            int idx = (i * size + j) * 3;
            data[idx + 0] = c;
            data[idx + 1] = c;
            data[idx + 2] = c;
        }
    }
}

void load_texture(void) {
    unsigned char* tex_data = malloc(TEX_SIZE * TEX_SIZE * 3);
    generate_checkerboard(tex_data, TEX_SIZE);
    
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TEX_SIZE, TEX_SIZE,
                      GL_RGB, GL_UNSIGNED_BYTE, tex_data);
    
    free(tex_data);
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void update_texture_params(void) {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    
    /* Filtering */
    switch (filter_mode) {
        case 0:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            printf("Filter: NEAREST\n");
            break;
        case 1:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            printf("Filter: LINEAR\n");
            break;
        case 2:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            printf("Filter: LINEAR_MIPMAP_LINEAR\n");
            break;
    }
    
    /* Wrapping */
    GLenum wrap = (wrap_mode == 0) ? GL_REPEAT : GL_CLAMP;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    printf("Wrap: %s\n", (wrap_mode == 0) ? "REPEAT" : "CLAMP");
}

void init_gl(void) {
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
    load_texture();
    update_texture_params();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
    
    glRotatef(rotation, 1.0f, 1.0f, 0.0f);
    
    /* Draw textured quad */
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f + tex_scroll, 0.0f); glVertex3f(-1.5f, -1.5f, 0.0f);
        glTexCoord2f(2.0f + tex_scroll, 0.0f); glVertex3f( 1.5f, -1.5f, 0.0f);
        glTexCoord2f(2.0f + tex_scroll, 2.0f); glVertex3f( 1.5f,  1.5f, 0.0f);
        glTexCoord2f(0.0f + tex_scroll, 2.0f); glVertex3f(-1.5f,  1.5f, 0.0f);
    glEnd();
    
    glutSwapBuffers();
}

void idle(void) {
    rotation += 0.3f;
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
        case 27: case 'q': case 'Q':
            glDeleteTextures(1, &texture_id);
            exit(0);
            break;
        case '1': case '2': case '3':
            filter_mode = key - '1';
            update_texture_params();
            break;
        case 'w': case 'W':
            wrap_mode = (wrap_mode + 1) % 2;
            update_texture_params();
            break;
        case 't': case 'T':
            tex_scroll += 0.1f;
            printf("Texture scroll: %.2f\n", tex_scroll);
            break;
    }
}

int main(int argc, char** argv) {
    printf("Chapter 9: Textures\n");
    printf("===================\n");
    printf("Controls:\n");
    printf("  1: NEAREST filtering\n");
    printf("  2: LINEAR filtering\n");
    printf("  3: LINEAR_MIPMAP_LINEAR filtering\n");
    printf("  W: Toggle wrap mode\n");
    printf("  T: Animate texture\n");
    printf("  ESC/Q: Quit\n\n");
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Chapter 9: Textures");
    
    init_gl();
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}

