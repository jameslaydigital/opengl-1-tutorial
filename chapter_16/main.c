/*
 * Chapter 16: Performance Tips
 * 
 * Demonstrates performance optimization techniques.
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define NUM_OBJECTS 500

static int render_mode = 0; /* 0=immediate, 1=vertex array, 2=display list */
static float rotation = 0.0f;
static GLuint display_list;
static int fps_count = 0;
static float fps = 0.0f;
static double last_fps_time = 0.0;

/* Vertex array data */
static GLfloat cube_vertices[] = {
    -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, /* Front */
    -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, /* Back */
    -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f, /* Top */
    -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, /* Bottom */
     0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f, /* Right */
    -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f  /* Left */
};

static GLfloat cube_colors[] = {
    1,0,0, 1,0,0, 1,0,0, 1,0,0,
    0,1,0, 0,1,0, 0,1,0, 0,1,0,
    0,0,1, 0,0,1, 0,0,1, 0,0,1,
    1,1,0, 1,1,0, 1,1,0, 1,1,0,
    1,0,1, 1,0,1, 1,0,1, 1,0,1,
    0,1,1, 0,1,1, 0,1,1, 0,1,1
};

double get_time(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

void draw_cube_immediate(void) {
    glBegin(GL_QUADS);
    for (int i = 0; i < 24; i++) {
        glColor3fv(&cube_colors[i*3]);
        glVertex3fv(&cube_vertices[i*3]);
    }
    glEnd();
}

void draw_cube_vertex_array(void) {
    glVertexPointer(3, GL_FLOAT, 0, cube_vertices);
    glColorPointer(3, GL_FLOAT, 0, cube_colors);
    glDrawArrays(GL_QUADS, 0, 24);
}

void create_display_list(void) {
    display_list = glGenLists(1);
    glNewList(display_list, GL_COMPILE);
    draw_cube_immediate();
    glEndList();
}

void init_gl(void) {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    create_display_list();
    last_fps_time = get_time();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 15, 30, 0, 0, 0, 0, 1, 0);
    
    /* Draw grid of cubes */
    for (int i = 0; i < NUM_OBJECTS; i++) {
        glPushMatrix();
        
        float angle = i * 7.2f + rotation;
        float radius = 5.0f + (i % 10) * 1.5f;
        float x = radius * cosf(angle * 0.017453f);
        float z = radius * sinf(angle * 0.017453f);
        float y = sinf(i * 0.3f + rotation * 0.05f) * 3.0f;
        
        glTranslatef(x, y, z);
        glRotatef(rotation * 2 + i * 10, 1, 1, 0);
        glScalef(0.5f, 0.5f, 0.5f);
        
        switch (render_mode) {
            case 0: draw_cube_immediate(); break;
            case 1: draw_cube_vertex_array(); break;
            case 2: glCallList(display_list); break;
        }
        
        glPopMatrix();
    }
    
    glutSwapBuffers();
    
    /* Update FPS */
    fps_count++;
    double current_time = get_time();
    if (current_time - last_fps_time >= 1.0) {
        fps = fps_count / (current_time - last_fps_time);
        fps_count = 0;
        last_fps_time = current_time;
        
        const char* mode_names[] = {"Immediate Mode", "Vertex Arrays", "Display Lists"};
        printf("Mode: %-20s | FPS: %.1f\n", mode_names[render_mode], fps);
    }
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
        case 27: case 'q': case 'Q':
            glDeleteLists(display_list, 1);
            exit(0);
            break;
        case '1':
            render_mode = 0;
            printf("\n=== Switched to Immediate Mode ===\n");
            fps_count = 0;
            last_fps_time = get_time();
            break;
        case '2':
            render_mode = 1;
            printf("\n=== Switched to Vertex Arrays ===\n");
            fps_count = 0;
            last_fps_time = get_time();
            break;
        case '3':
            render_mode = 2;
            printf("\n=== Switched to Display Lists ===\n");
            fps_count = 0;
            last_fps_time = get_time();
            break;
    }
}

int main(int argc, char** argv) {
    printf("Chapter 16: Performance Tips\n");
    printf("============================\n");
    printf("Rendering %d animated cubes\n", NUM_OBJECTS);
    printf("\nControls:\n");
    printf("  1: Immediate mode (slowest)\n");
    printf("  2: Vertex arrays (faster)\n");
    printf("  3: Display lists (fastest for static geometry)\n");
    printf("  ESC/Q: Quit\n\n");
    printf("Watch the FPS counter to see performance differences!\n\n");
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 700);
    glutCreateWindow("Chapter 16: Performance Tips");
    
    init_gl();
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}

