/*
 * Chapter 5: Drawing in Immediate Mode
 * 
 * Demonstrates all OpenGL primitive types and immediate mode rendering.
 */

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "primitives.h"

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 700

/* Demo mode */
static int demo_mode = 0;
static int num_modes = 8;

/*
 * init_gl - Initialize OpenGL state
 */
void init_gl(void) {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glShadeModel(GL_SMOOTH);
}

/*
 * demo_primitives - Demonstrate different primitive types
 */
void demo_primitives(void) {
    float y = 0.7f;
    float spacing = 0.3f;
    
    /* Points */
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        for (int i = 0; i < 10; i++) {
            glVertex2f(-0.8f + i * 0.18f, y);
        }
    glEnd();
    y -= spacing;
    
    /* Lines */
    glLineWidth(2.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.8f, y); glVertex2f(-0.4f, y);
        glVertex2f(-0.2f, y); glVertex2f(0.2f, y);
        glVertex2f(0.4f, y); glVertex2f(0.8f, y);
    glEnd();
    y -= spacing;
    
    /* Line Strip */
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
        for (int i = 0; i < 10; i++) {
            glVertex2f(-0.8f + i * 0.18f, y + (i % 2) * 0.1f);
        }
    glEnd();
    y -= spacing;
    
    /* Line Loop */
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.3f, y + 0.1f);
        glVertex2f(-0.1f, y + 0.1f);
        glVertex2f(-0.1f, y - 0.1f);
        glVertex2f(-0.3f, y - 0.1f);
    glEnd();
    
    /* Triangles */
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.2f, y + 0.1f);
        glVertex2f(0.3f, y - 0.1f);
        glVertex2f(0.4f, y + 0.1f);
    glEnd();
    
    /* Quad */
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(0.5f, y + 0.1f);
        glVertex2f(0.7f, y + 0.1f);
        glVertex2f(0.7f, y - 0.1f);
        glVertex2f(0.5f, y - 0.1f);
    glEnd();
}

/*
 * demo_colored_triangle - Smooth shaded triangle
 */
void demo_colored_triangle(void) {
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 0.6f);
        
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-0.6f, -0.4f);
        
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.6f, -0.4f);
    glEnd();
}

/*
 * demo_triangle_strip - Efficient triangle mesh
 */
void demo_triangle_strip(void) {
    int segments = 20;
    float width = 1.6f;
    float height = 0.8f;
    
    glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= segments; i++) {
            float t = (float)i / segments;
            float x = -width/2 + width * t;
            float wave = 0.2f * sinf(t * 6.28f * 3);
            
            float hue1 = t;
            glColor3f(hue1, 0.5f, 1.0f - hue1);
            glVertex2f(x, height/2 + wave);
            
            float hue2 = t * 0.7f;
            glColor3f(1.0f - hue2, 0.3f, hue2);
            glVertex2f(x, -height/2 + wave);
        }
    glEnd();
}

/*
 * demo_circle - Draw circles using triangle fan
 */
void demo_circle(void) {
    /* Filled circle */
    draw_circle(-0.4f, 0.2f, 0.3f, 50);
    
    /* Circle outline */
    glLineWidth(3.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    draw_circle_outline(0.4f, 0.2f, 0.3f, 50);
    
    /* Multiple circles */
    for (int i = 0; i < 5; i++) {
        float hue = (float)i / 5.0f;
        glColor3f(hue, 1.0f - hue, 0.5f);
        draw_circle(-0.6f + i * 0.3f, -0.4f, 0.12f, 30);
    }
}

/*
 * demo_polygon_modes - Show different polygon rendering modes
 */
void demo_polygon_modes(void) {
    float size = 0.25f;
    
    /* Filled */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.0f, 0.8f, 0.8f);
    glPushMatrix();
    glTranslatef(-0.5f, 0.3f, 0.0f);
    draw_hexagon(0.0f, 0.0f, size);
    glPopMatrix();
    
    /* Wireframe */
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1.0f, 0.5f, 0.0f);
    glLineWidth(2.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.0f);
    draw_hexagon(0.0f, 0.0f, size);
    glPopMatrix();
    
    /* Point mode */
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glColor3f(1.0f, 1.0f, 0.0f);
    glPointSize(8.0f);
    glPushMatrix();
    glTranslatef(0.5f, 0.3f, 0.0f);
    draw_hexagon(0.0f, 0.0f, size);
    glPopMatrix();
    
    /* Reset to fill mode */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    /* Draw star */
    glColor3f(1.0f, 1.0f, 0.3f);
    draw_star(0.0f, -0.3f, 0.3f, 0.15f, 5);
}

/*
 * demo_grid - Draw a colorful grid
 */
void demo_grid(void) {
    int rows = 10;
    int cols = 15;
    float cell_width = 1.6f / cols;
    float cell_height = 1.4f / rows;
    
    glBegin(GL_QUADS);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float x = -0.8f + j * cell_width;
            float y = 0.7f - i * cell_height;
            
            /* Checkerboard pattern */
            if ((i + j) % 2 == 0) {
                glColor3f(0.2f, 0.2f, 0.3f);
            } else {
                float hue = (float)(i * cols + j) / (rows * cols);
                glColor3f(hue, 0.5f, 1.0f - hue);
            }
            
            glVertex2f(x, y);
            glVertex2f(x + cell_width, y);
            glVertex2f(x + cell_width, y - cell_height);
            glVertex2f(x, y - cell_height);
        }
    }
    glEnd();
}

/*
 * demo_spiral - Draw a colorful spiral
 */
void demo_spiral(void) {
    float max_radius = 0.7f;
    int segments = 200;
    
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= segments; i++) {
        float t = (float)i / segments;
        float angle = t * 6.28f * 8;  /* 8 rotations */
        float radius = t * max_radius;
        
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        
        glColor3f(t, 1.0f - t, 0.5f);
        glVertex2f(x, y);
    }
    glEnd();
}

/*
 * demo_smooth_vs_flat - Compare shading models
 */
void demo_smooth_vs_flat(void) {
    float size = 0.3f;
    
    /* Smooth shading (left) */
    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.4f, 0.0f);
        for (int i = 0; i <= 6; i++) {
            float angle = (float)i / 6.0f * 6.28f;
            float hue = (float)i / 6.0f;
            glColor3f(hue, 1.0f - hue, 0.5f);
            glVertex2f(-0.4f + size * cosf(angle), size * sinf(angle));
        }
    glEnd();
    
    /* Flat shading (right) */
    glShadeModel(GL_FLAT);
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0.4f, 0.0f);
        for (int i = 0; i <= 6; i++) {
            float angle = (float)i / 6.0f * 6.28f;
            float hue = (float)i / 6.0f;
            glColor3f(hue, 1.0f - hue, 0.5f);
            glVertex2f(0.4f + size * cosf(angle), size * sinf(angle));
        }
    glEnd();
    
    /* Reset to smooth */
    glShadeModel(GL_SMOOTH);
}

/*
 * display - GLUT display callback
 */
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    /* Draw based on current mode */
    switch (demo_mode) {
        case 0: demo_primitives(); break;
        case 1: demo_colored_triangle(); break;
        case 2: demo_triangle_strip(); break;
        case 3: demo_circle(); break;
        case 4: demo_polygon_modes(); break;
        case 5: demo_grid(); break;
        case 6: demo_spiral(); break;
        case 7: demo_smooth_vs_flat(); break;
    }
    
    glutSwapBuffers();
}

/*
 * keyboard - GLUT keyboard callback
 */
void keyboard(unsigned char key, int x, int y) {
    (void)x; (void)y;
    
    switch (key) {
        case 27: /* ESC */
        case 'q':
        case 'Q':
            exit(0);
            break;
            
        case ' ':
        case 'n':
        case 'N':
            demo_mode = (demo_mode + 1) % num_modes;
            printf("Demo mode: %d\n", demo_mode);
            glutPostRedisplay();
            break;
            
        case '0': case '1': case '2': case '3':
        case '4': case '5': case '6': case '7':
            demo_mode = key - '0';
            if (demo_mode < num_modes) {
                printf("Demo mode: %d\n", demo_mode);
                glutPostRedisplay();
            }
            break;
    }
}

/*
 * print_instructions - Print controls
 */
void print_instructions(void) {
    printf("Chapter 5: Drawing in Immediate Mode\n");
    printf("=====================================\n");
    printf("Demo Modes:\n");
    printf("  0 - All primitive types\n");
    printf("  1 - Colored triangle (smooth shading)\n");
    printf("  2 - Triangle strip (wavy ribbon)\n");
    printf("  3 - Circles\n");
    printf("  4 - Polygon modes (fill/line/point)\n");
    printf("  5 - Grid\n");
    printf("  6 - Spiral\n");
    printf("  7 - Smooth vs Flat shading\n");
    printf("\nControls:\n");
    printf("  0-7    - Switch demo mode\n");
    printf("  Space  - Next demo\n");
    printf("  ESC/Q  - Quit\n");
    printf("\n");
}

/*
 * main - Entry point
 */
int main(int argc, char** argv) {
    print_instructions();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Chapter 5: Drawing in Immediate Mode");
    
    init_gl();
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}

