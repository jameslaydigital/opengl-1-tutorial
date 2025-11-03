/*
 * primitives.c - Helper functions for drawing shapes
 */

#include <GL/glut.h>
#include <math.h>
#include "primitives.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
 * draw_circle - Draw a filled circle
 */
void draw_circle(float cx, float cy, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        
        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * M_PI * i / segments;
            float x = cx + radius * cosf(angle);
            float y = cy + radius * sinf(angle);
            glVertex2f(x, y);
        }
    glEnd();
}

/*
 * draw_circle_outline - Draw a circle outline
 */
void draw_circle_outline(float cx, float cy, float radius, int segments) {
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < segments; i++) {
            float angle = 2.0f * M_PI * i / segments;
            float x = cx + radius * cosf(angle);
            float y = cy + radius * sinf(angle);
            glVertex2f(x, y);
        }
    glEnd();
}

/*
 * draw_hexagon - Draw a hexagon
 */
void draw_hexagon(float cx, float cy, float radius) {
    glBegin(GL_POLYGON);
        for (int i = 0; i < 6; i++) {
            float angle = M_PI / 3.0f * i;
            float x = cx + radius * cosf(angle);
            float y = cy + radius * sinf(angle);
            glVertex2f(x, y);
        }
    glEnd();
}

/*
 * draw_star - Draw a star shape
 */
void draw_star(float cx, float cy, float outer_radius, float inner_radius, int points) {
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        
        for (int i = 0; i <= points * 2; i++) {
            float angle = M_PI * i / points - M_PI / 2;
            float radius = (i % 2 == 0) ? outer_radius : inner_radius;
            float x = cx + radius * cosf(angle);
            float y = cy + radius * sinf(angle);
            glVertex2f(x, y);
        }
    glEnd();
}

