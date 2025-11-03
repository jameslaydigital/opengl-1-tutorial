/*
 * Chapter 4: GLUT 101 - Window + Main Loop
 * 
 * Demonstrates all major GLUT callbacks and features.
 */

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Window dimensions */
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

/* Application state */
static struct {
    float square_x;
    float square_y;
    float square_size;
    float rotation;
    float color_r;
    float color_g;
    float color_b;
    int last_time;
    int frame_count;
    float fps;
    bool fullscreen;
} app_state = {
    .square_x = 0.0f,
    .square_y = 0.0f,
    .square_size = 0.2f,
    .rotation = 0.0f,
    .color_r = 1.0f,
    .color_g = 0.5f,
    .color_b = 0.0f,
    .last_time = 0,
    .frame_count = 0,
    .fps = 0.0f,
    .fullscreen = false
};

/*
 * init_gl - Initialize OpenGL state
 */
void init_gl(void) {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glShadeModel(GL_SMOOTH);
    
    printf("OpenGL initialized\n");
    printf("  Version: %s\n", glGetString(GL_VERSION));
}

/*
 * draw_square - Draw a colored square
 */
void draw_square(float x, float y, float size, float rotation) {
    glPushMatrix();
    
    glTranslatef(x, y, 0.0f);
    glRotatef(rotation, 0.0f, 0.0f, 1.0f);
    
    glBegin(GL_QUADS);
        glColor3f(app_state.color_r, app_state.color_g, app_state.color_b);
        glVertex2f(-size, -size);
        glVertex2f(size, -size);
        glVertex2f(size, size);
        glVertex2f(-size, size);
    glEnd();
    
    glPopMatrix();
}

/*
 * display - GLUT display callback
 */
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Draw the square */
    draw_square(app_state.square_x, app_state.square_y, 
                app_state.square_size, app_state.rotation);
    
    /* Draw FPS counter (just a simple indicator) */
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glutSwapBuffers();
    
    /* Update frame count */
    app_state.frame_count++;
}

/*
 * idle - GLUT idle callback
 */
void idle(void) {
    int current_time = glutGet(GLUT_ELAPSED_TIME);
    float delta = (current_time - app_state.last_time) / 1000.0f;
    
    /* Update FPS counter every second */
    if (current_time - app_state.last_time >= 1000) {
        app_state.fps = app_state.frame_count / delta;
        printf("FPS: %.1f\n", app_state.fps);
        app_state.frame_count = 0;
        app_state.last_time = current_time;
    }
    
    /* Animate rotation */
    app_state.rotation += 30.0f * delta;
    if (app_state.rotation >= 360.0f) {
        app_state.rotation -= 360.0f;
    }
    
    /* Request redraw */
    glutPostRedisplay();
}

/*
 * reshape - GLUT reshape callback
 */
void reshape(int width, int height) {
    printf("Window reshaped to %dx%d\n", width, height);
    
    /* Prevent division by zero */
    height = (height == 0) ? 1 : height;
    
    /* Update viewport */
    glViewport(0, 0, width, height);
    
    /* Set up orthographic projection (2D) */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aspect = (float)width / (float)height;
    if (width >= height) {
        glOrtho(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
    } else {
        glOrtho(-1.0, 1.0, -1.0/aspect, 1.0/aspect, -1.0, 1.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
 * keyboard - GLUT keyboard callback
 */
void keyboard(unsigned char key, int x, int y) {
    (void)x;
    (void)y;
    
    switch (key) {
        case 27:  /* ESC */
        case 'q':
        case 'Q':
            printf("Exiting...\n");
            exit(0);
            break;
            
        case 'f':
        case 'F':
            app_state.fullscreen = !app_state.fullscreen;
            if (app_state.fullscreen) {
                glutFullScreen();
                printf("Fullscreen enabled\n");
            } else {
                glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
                printf("Fullscreen disabled\n");
            }
            break;
            
        case 'r':
        case 'R':
            app_state.square_x = 0.0f;
            app_state.square_y = 0.0f;
            app_state.rotation = 0.0f;
            printf("Position reset\n");
            break;
            
        case ' ':
            /* Change color randomly */
            app_state.color_r = (float)rand() / RAND_MAX;
            app_state.color_g = (float)rand() / RAND_MAX;
            app_state.color_b = (float)rand() / RAND_MAX;
            printf("Color changed\n");
            break;
            
        default:
            printf("Key pressed: '%c' (0x%02x)\n", key, key);
            break;
    }
}

/*
 * special - GLUT special keys callback
 */
void special(int key, int x, int y) {
    (void)x;
    (void)y;
    
    const float move_speed = 0.05f;
    
    switch (key) {
        case GLUT_KEY_UP:
            app_state.square_y += move_speed;
            printf("Move up: y = %.2f\n", app_state.square_y);
            break;
            
        case GLUT_KEY_DOWN:
            app_state.square_y -= move_speed;
            printf("Move down: y = %.2f\n", app_state.square_y);
            break;
            
        case GLUT_KEY_LEFT:
            app_state.square_x -= move_speed;
            printf("Move left: x = %.2f\n", app_state.square_x);
            break;
            
        case GLUT_KEY_RIGHT:
            app_state.square_x += move_speed;
            printf("Move right: x = %.2f\n", app_state.square_x);
            break;
            
        case GLUT_KEY_F1:
            printf("F1 pressed\n");
            break;
            
        default:
            printf("Special key pressed: %d\n", key);
            break;
    }
}

/*
 * mouse - GLUT mouse button callback
 */
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        switch (button) {
            case GLUT_LEFT_BUTTON:
                /* Change color on left click */
                app_state.color_r = (float)rand() / RAND_MAX;
                app_state.color_g = (float)rand() / RAND_MAX;
                app_state.color_b = (float)rand() / RAND_MAX;
                printf("Left click at (%d, %d) - color changed\n", x, y);
                break;
                
            case GLUT_RIGHT_BUTTON:
                printf("Right click at (%d, %d)\n", x, y);
                break;
                
            case GLUT_MIDDLE_BUTTON:
                printf("Middle click at (%d, %d)\n", x, y);
                break;
                
            default:
                break;
        }
    }
}

/*
 * motion - GLUT mouse motion callback (button held)
 */
void motion(int x, int y) {
    /* Convert window coordinates to OpenGL coordinates */
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    
    float aspect = (float)width / (float)height;
    app_state.square_x = ((float)x / width * 2.0f - 1.0f) * aspect;
    app_state.square_y = -((float)y / height * 2.0f - 1.0f);
    
    printf("Mouse dragged to (%d, %d) -> square at (%.2f, %.2f)\n", 
           x, y, app_state.square_x, app_state.square_y);
}

/*
 * passive_motion - GLUT passive mouse motion callback (no button)
 */
void passive_motion(int x, int y) {
    /* This gets called a LOT, so don't print unless needed */
    (void)x;
    (void)y;
}

/*
 * main - Entry point
 */
int main(int argc, char** argv) {
    printf("Chapter 4: GLUT 101 - Window + Main Loop\n");
    printf("=========================================\n");
    printf("Controls:\n");
    printf("  Arrow Keys - Move square\n");
    printf("  Space      - Random color\n");
    printf("  Left Click - Random color\n");
    printf("  Drag       - Move square to mouse\n");
    printf("  F          - Toggle fullscreen\n");
    printf("  R          - Reset position\n");
    printf("  ESC/Q      - Quit\n");
    printf("\n");
    
    /* Initialize GLUT */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Chapter 4: GLUT 101");
    
    /* Initialize OpenGL */
    init_gl();
    
    /* Register callbacks */
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passive_motion);
    
    /* Initialize timing */
    app_state.last_time = glutGet(GLUT_ELAPSED_TIME);
    
    /* Enter main loop */
    glutMainLoop();
    
    return 0;
}

