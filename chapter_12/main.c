/* Chapter 12: Vertex Arrays */
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define GRID_SIZE 50

static GLfloat vertices[GRID_SIZE * GRID_SIZE * 3];
static GLfloat colors[GRID_SIZE * GRID_SIZE * 3];
static GLuint indices[(GRID_SIZE-1) * (GRID_SIZE-1) * 6];
static float rotation = 0.0f;

void generate_terrain(void) {
    int idx = 0;
    for (int z = 0; z < GRID_SIZE; z++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            float fx = (x - GRID_SIZE/2) * 0.2f;
            float fz = (z - GRID_SIZE/2) * 0.2f;
            float fy = sinf(fx*0.5f) * cosf(fz*0.5f);
            
            vertices[idx*3+0] = fx;
            vertices[idx*3+1] = fy;
            vertices[idx*3+2] = fz;
            
            colors[idx*3+0] = 0.2f + fy*0.5f;
            colors[idx*3+1] = 0.8f - fy*0.3f;
            colors[idx*3+2] = 0.3f;
            idx++;
        }
    }
    
    idx = 0;
    for (int z = 0; z < GRID_SIZE-1; z++) {
        for (int x = 0; x < GRID_SIZE-1; x++) {
            int i0 = z * GRID_SIZE + x;
            int i1 = i0 + 1;
            int i2 = i0 + GRID_SIZE;
            int i3 = i2 + 1;
            
            indices[idx++] = i0;
            indices[idx++] = i2;
            indices[idx++] = i1;
            
            indices[idx++] = i1;
            indices[idx++] = i2;
            indices[idx++] = i3;
        }
    }
}

void init_gl(void) {
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    generate_terrain();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 5, 10, 0, 0, 0, 0, 1, 0);
    glRotatef(rotation, 0, 1, 0);
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    
    glDrawElements(GL_TRIANGLES, (GRID_SIZE-1)*(GRID_SIZE-1)*6, 
                   GL_UNSIGNED_INT, indices);
    
    glutSwapBuffers();
}

void idle(void) {
    rotation += 0.3f;
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
    if (key == 'w') {
        static int wireframe = 0;
        wireframe = !wireframe;
        glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    }
}

int main(int argc, char** argv) {
    printf("Chapter 12: Vertex Arrays\nRendering %dx%d terrain grid\nW: Toggle wireframe\n", 
           GRID_SIZE, GRID_SIZE);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Chapter 12: Vertex Arrays");
    init_gl();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

