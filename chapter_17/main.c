/*
 * Chapter 17: Debugging & Introspection
 * 
 * Demonstrates OpenGL debugging techniques.
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static float rotation = 0.0f;
static int show_normals = 1;
static int wireframe = 0;

void check_gl_error(const char* context) {
    GLenum err;
    int error_count = 0;
    
    while ((err = glGetError()) != GL_NO_ERROR) {
        const char* error_str = "Unknown error";
        switch (err) {
            case GL_INVALID_ENUM: error_str = "GL_INVALID_ENUM"; break;
            case GL_INVALID_VALUE: error_str = "GL_INVALID_VALUE"; break;
            case GL_INVALID_OPERATION: error_str = "GL_INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW: error_str = "GL_STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW: error_str = "GL_STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY: error_str = "GL_OUT_OF_MEMORY"; break;
        }
        fprintf(stderr, "OpenGL error in %s: %s (0x%x)\n", context, error_str, err);
        error_count++;
    }
    
    if (error_count > 0) {
        fprintf(stderr, "Total errors in %s: %d\n", context, error_count);
    }
}

void print_gl_info(void) {
    printf("\n=== OpenGL Information ===\n");
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));
    
    GLint max_texture_size, max_lights, max_modelview_stack_depth;
    GLint max_projection_stack_depth, max_viewport_dims[2];
    
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_texture_size);
    glGetIntegerv(GL_MAX_LIGHTS, &max_lights);
    glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &max_modelview_stack_depth);
    glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &max_projection_stack_depth);
    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, max_viewport_dims);
    
    printf("\n=== Capabilities ===\n");
    printf("Max texture size: %d x %d\n", max_texture_size, max_texture_size);
    printf("Max lights: %d\n", max_lights);
    printf("Max modelview stack depth: %d\n", max_modelview_stack_depth);
    printf("Max projection stack depth: %d\n", max_projection_stack_depth);
    printf("Max viewport dimensions: %d x %d\n", max_viewport_dims[0], max_viewport_dims[1]);
    
    printf("\n=== Current State ===\n");
    GLboolean depth_test, lighting, blend, cull_face;
    glGetBooleanv(GL_DEPTH_TEST, &depth_test);
    glGetBooleanv(GL_LIGHTING, &lighting);
    glGetBooleanv(GL_BLEND, &blend);
    glGetBooleanv(GL_CULL_FACE, &cull_face);
    
    printf("Depth test: %s\n", depth_test ? "ON" : "OFF");
    printf("Lighting: %s\n", lighting ? "ON" : "OFF");
    printf("Blending: %s\n", blend ? "ON" : "OFF");
    printf("Culling: %s\n", cull_face ? "ON" : "OFF");
    printf("\n");
}

/* Draw normal vectors for visualization */
void draw_normal(float x, float y, float z, float nx, float ny, float nz) {
    float length = 0.3f;
    glBegin(GL_LINES);
        glVertex3f(x, y, z);
        glVertex3f(x + nx * length, y + ny * length, z + nz * length);
    glEnd();
}

void draw_cube_with_normal_viz(float size) {
    float h = size / 2;
    
    glEnable(GL_LIGHTING);
    glBegin(GL_QUADS);
    
    /* Front face */
    glNormal3f(0, 0, 1);
    glColor3f(1, 0, 0);
    glVertex3f(-h, -h,  h);
    glVertex3f( h, -h,  h);
    glVertex3f( h,  h,  h);
    glVertex3f(-h,  h,  h);
    
    /* Back face */
    glNormal3f(0, 0, -1);
    glColor3f(0, 1, 0);
    glVertex3f(-h, -h, -h);
    glVertex3f(-h,  h, -h);
    glVertex3f( h,  h, -h);
    glVertex3f( h, -h, -h);
    
    /* Top face */
    glNormal3f(0, 1, 0);
    glColor3f(0, 0, 1);
    glVertex3f(-h,  h, -h);
    glVertex3f(-h,  h,  h);
    glVertex3f( h,  h,  h);
    glVertex3f( h,  h, -h);
    
    /* Bottom face */
    glNormal3f(0, -1, 0);
    glColor3f(1, 1, 0);
    glVertex3f(-h, -h, -h);
    glVertex3f( h, -h, -h);
    glVertex3f( h, -h,  h);
    glVertex3f(-h, -h,  h);
    
    /* Right face */
    glNormal3f(1, 0, 0);
    glColor3f(1, 0, 1);
    glVertex3f( h, -h, -h);
    glVertex3f( h,  h, -h);
    glVertex3f( h,  h,  h);
    glVertex3f( h, -h,  h);
    
    /* Left face */
    glNormal3f(-1, 0, 0);
    glColor3f(0, 1, 1);
    glVertex3f(-h, -h, -h);
    glVertex3f(-h, -h,  h);
    glVertex3f(-h,  h,  h);
    glVertex3f(-h,  h, -h);
    
    glEnd();
    
    /* Draw normal vectors */
    if (show_normals) {
        glDisable(GL_LIGHTING);
        glColor3f(1, 1, 0);
        glLineWidth(2.0f);
        
        draw_normal(0, 0,  h, 0, 0, 1);   /* Front */
        draw_normal(0, 0, -h, 0, 0, -1);  /* Back */
        draw_normal(0,  h, 0, 0, 1, 0);   /* Top */
        draw_normal(0, -h, 0, 0, -1, 0);  /* Bottom */
        draw_normal( h, 0, 0, 1, 0, 0);   /* Right */
        draw_normal(-h, 0, 0, -1, 0, 0);  /* Left */
        
        glLineWidth(1.0f);
        glEnable(GL_LIGHTING);
    }
}

void init_gl(void) {
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_NORMALIZE);
    
    GLfloat light_pos[] = {5, 5, 5, 1};
    GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1};
    GLfloat light_diffuse[] = {1, 1, 1, 1};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    
    check_gl_error("init_gl");
    print_gl_info();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 3, 8, 0, 0, 0, 0, 1, 0);
    
    GLfloat light_pos[] = {5, 5, 5, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    glPushMatrix();
    glRotatef(rotation, 1, 1, 0);
    draw_cube_with_normal_viz(2.0);
    glPopMatrix();
    
    glutSwapBuffers();
    check_gl_error("display");
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
    check_gl_error("reshape");
}

void keyboard(unsigned char key, int x, int y) {
    (void)x; (void)y;
    
    switch (key) {
        case 27: case 'q': case 'Q': exit(0); break;
        case 'n': case 'N':
            show_normals = !show_normals;
            printf("Show normals: %s\n", show_normals ? "ON" : "OFF");
            break;
        case 'w': case 'W':
            wireframe = !wireframe;
            glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
            printf("Wireframe: %s\n", wireframe ? "ON" : "OFF");
            break;
        case 'i': case 'I':
            print_gl_info();
            break;
    }
}

int main(int argc, char** argv) {
    printf("Chapter 17: Debugging & Introspection\n");
    printf("======================================\n");
    printf("Controls:\n");
    printf("  N: Toggle normal visualization\n");
    printf("  W: Toggle wireframe\n");
    printf("  I: Print GL info\n");
    printf("  ESC/Q: Quit\n");
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Chapter 17: Debugging & Introspection");
    
    init_gl();
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}

