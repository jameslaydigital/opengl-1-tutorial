/*
 * render.c - Rendering implementation
 */

#include <GL/glut.h>
#include <math.h>
#include "render.h"

/* Animation angle */
static float rotation_angle = 0.0f;

/*
 * init_render - Initialize OpenGL rendering state
 */
void init_render(void) {
    /* Set clear color to dark blue */
    glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
    
    /* Enable depth testing */
    glEnable(GL_DEPTH_TEST);
    
    /* Use smooth shading */
    glShadeModel(GL_SMOOTH);
}

/*
 * render_scene - Render the entire scene
 */
void render_scene(void) {
    /* Clear buffers */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Reset transformations */
    glLoadIdentity();
    
    /* Apply rotation (animated) */
    glRotatef(rotation_angle, 0.0f, 0.0f, 1.0f);
    
    /* Draw a colored triangle */
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);  /* Red */
        glVertex2f(0.0f, 0.5f);
        
        glColor3f(0.0f, 1.0f, 0.0f);  /* Green */
        glVertex2f(-0.5f, -0.5f);
        
        glColor3f(0.0f, 0.0f, 1.0f);  /* Blue */
        glVertex2f(0.5f, -0.5f);
    glEnd();
    
    /* Update animation */
    rotation_angle += 0.5f;
    if (rotation_angle >= 360.0f) {
        rotation_angle -= 360.0f;
    }
}

