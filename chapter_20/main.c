/*
 * Chapter 20: Exercises & Mini-Projects
 * 
 * Showcases several mini-projects demonstrating various OpenGL techniques.
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_PARTICLES 200

static int demo_mode = 0;
static float rotation = 0.0f;
static int terrain_size = 30;

/* Particle system */
typedef struct {
    float x, y, z;
    float vx, vy, vz;
    float life;
    float r, g, b;
} particle_t;

static particle_t particles[MAX_PARTICLES];

void init_particles(void) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].x = 0;
        particles[i].y = 0;
        particles[i].z = 0;
        particles[i].vx = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
        particles[i].vy = (float)rand() / RAND_MAX * 0.2f;
        particles[i].vz = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
        particles[i].life = (float)rand() / RAND_MAX;
        particles[i].r = 1.0f;
        particles[i].g = 0.5f + (float)rand() / RAND_MAX * 0.5f;
        particles[i].b = 0.0f;
    }
}

void update_particles(float dt) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].x += particles[i].vx * dt;
        particles[i].y += particles[i].vy * dt;
        particles[i].z += particles[i].vz * dt;
        particles[i].vy -= 0.001f; /* Gravity */
        particles[i].life -= dt * 0.01f;
        
        if (particles[i].life <= 0.0f) {
            particles[i].x = 0;
            particles[i].y = 0;
            particles[i].z = 0;
            particles[i].vx = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
            particles[i].vy = (float)rand() / RAND_MAX * 0.2f;
            particles[i].vz = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
            particles[i].life = 1.0f;
        }
    }
}

/* Project 1: Spinning Lit Cube */
void project_spinning_cube(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    GLfloat light_pos[] = {5, 5, 5, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    glPushMatrix();
    glRotatef(rotation, 1, 1, 1);
    
    glBegin(GL_QUADS);
    float colors[][3] = {{1,0,0}, {0,1,0}, {0,0,1}, {1,1,0}, {1,0,1}, {0,1,1}};
    float h = 1.0f;
    
    /* Draw cube with per-face colors and normals */
    glColor3fv(colors[0]); glNormal3f(0,0,1);
    glVertex3f(-h,-h,h); glVertex3f(h,-h,h); glVertex3f(h,h,h); glVertex3f(-h,h,h);
    
    glColor3fv(colors[1]); glNormal3f(0,0,-1);
    glVertex3f(-h,-h,-h); glVertex3f(-h,h,-h); glVertex3f(h,h,-h); glVertex3f(h,-h,-h);
    
    glColor3fv(colors[2]); glNormal3f(0,1,0);
    glVertex3f(-h,h,-h); glVertex3f(-h,h,h); glVertex3f(h,h,h); glVertex3f(h,h,-h);
    
    glColor3fv(colors[3]); glNormal3f(0,-1,0);
    glVertex3f(-h,-h,-h); glVertex3f(h,-h,-h); glVertex3f(h,-h,h); glVertex3f(-h,-h,h);
    
    glColor3fv(colors[4]); glNormal3f(1,0,0);
    glVertex3f(h,-h,-h); glVertex3f(h,h,-h); glVertex3f(h,h,h); glVertex3f(h,-h,h);
    
    glColor3fv(colors[5]); glNormal3f(-1,0,0);
    glVertex3f(-h,-h,-h); glVertex3f(-h,-h,h); glVertex3f(-h,h,h); glVertex3f(-h,h,-h);
    glEnd();
    
    glPopMatrix();
}

/* Project 2: Teapot Material Showcase */
void project_teapot_materials(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    GLfloat light_pos[] = {5, 5, 5, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    /* Three teapots with different materials */
    static int material = 0;
    material = ((int)(rotation / 60.0f)) % 3;
    
    GLfloat materials[][4] = {
        {0.75f, 0.61f, 0.23f, 1.0f}, /* Gold diffuse */
        {0.51f, 0.51f, 0.51f, 1.0f}, /* Silver diffuse */
        {0.55f, 0.0f, 0.0f, 1.0f}     /* Ruby diffuse */
    };
    
    GLfloat specular[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat shininess = 50.0f;
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[material]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(rotation, 0, 0, 1);
    glutSolidTeapot(1.5);
    glPopMatrix();
}

/* Project 3: Particle System */
void project_particles(void) {
    static int last_time = 0;
    int current_time = glutGet(GLUT_ELAPSED_TIME);
    float dt = (current_time - last_time) / 16.0f;
    last_time = current_time;
    
    update_particles(dt);
    
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDepthMask(GL_FALSE);
    
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < MAX_PARTICLES; i++) {
        float alpha = particles[i].life;
        glColor4f(particles[i].r, particles[i].g, particles[i].b, alpha);
        glVertex3f(particles[i].x, particles[i].y, particles[i].z);
    }
    glEnd();
    
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

/* Project 4: Simple Terrain */
void project_terrain(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    GLfloat light_pos[] = {10, 10, 10, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    float scale = 0.3f;
    glPushMatrix();
    glRotatef(rotation * 0.5f, 0, 1, 0);
    
    for (int z = 0; z < terrain_size - 1; z++) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int x = 0; x < terrain_size; x++) {
            float fx = (x - terrain_size/2) * scale;
            float fz = (z - terrain_size/2) * scale;
            
            float y1 = sinf(fx * 0.5f) * cosf(fz * 0.5f) * 1.5f;
            float y2 = sinf(fx * 0.5f) * cosf((fz + scale) * 0.5f) * 1.5f;
            
            float height1 = (y1 + 2.0f) / 4.0f;
            float height2 = (y2 + 2.0f) / 4.0f;
            
            glColor3f(0.2f + height1 * 0.5f, 0.8f - height1 * 0.3f, 0.3f);
            glVertex3f(fx, y1, fz);
            
            glColor3f(0.2f + height2 * 0.5f, 0.8f - height2 * 0.3f, 0.3f);
            glVertex3f(fx, y2, fz + scale);
        }
        glEnd();
    }
    
    glPopMatrix();
}

/* Project 5: Solar System */
void project_solar_system(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    GLfloat light_pos[] = {0, 0, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    /* Sun */
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidSphere(0.5, 20, 20);
    
    /* Earth orbit */
    glPushMatrix();
    glRotatef(rotation, 0, 1, 0);
    glTranslatef(3.0f, 0, 0);
    glColor3f(0.2f, 0.5f, 1.0f);
    glutSolidSphere(0.3, 15, 15);
    
    /* Moon orbit */
    glPushMatrix();
    glRotatef(rotation * 3, 0, 1, 0);
    glTranslatef(0.6f, 0, 0);
    glColor3f(0.7f, 0.7f, 0.7f);
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();
    
    glPopMatrix();
    
    /* Mars orbit */
    glPushMatrix();
    glRotatef(rotation * 0.7f, 0, 1, 0);
    glTranslatef(5.0f, 0, 0);
    glColor3f(1.0f, 0.3f, 0.0f);
    glutSolidSphere(0.25, 15, 15);
    glPopMatrix();
    
    glPopMatrix();
}

void init_gl(void) {
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    srand(time(NULL));
    init_particles();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 3, 8, 0, 0, 0, 0, 1, 0);
    
    switch (demo_mode) {
        case 0: project_spinning_cube(); break;
        case 1: project_teapot_materials(); break;
        case 2: project_particles(); break;
        case 3: project_terrain(); break;
        case 4: project_solar_system(); break;
    }
    
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
        case '1': case '2': case '3': case '4': case '5':
            demo_mode = key - '1';
            rotation = 0.0f;
            printf("Project %d\n", demo_mode + 1);
            break;
    }
}

int main(int argc, char** argv) {
    printf("Chapter 20: Exercises & Mini-Projects\n");
    printf("======================================\n");
    printf("Projects:\n");
    printf("  1 - Spinning Lit Cube (6 colored faces)\n");
    printf("  2 - Teapot Material Showcase (cycling materials)\n");
    printf("  3 - Particle System (fire effect with blending)\n");
    printf("  4 - Terrain from Heightmap (procedural terrain)\n");
    printf("  5 - Solar System (hierarchical transforms)\n");
    printf("\nControls:\n");
    printf("  1-5: Switch project\n");
    printf("  ESC/Q: Quit\n\n");
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 700);
    glutCreateWindow("Chapter 20: Exercises & Mini-Projects");
    
    init_gl();
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}

