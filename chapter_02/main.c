/*
 * Chapter 2: Hello Window
 * 
 * This program creates a simple OpenGL window and fills it with a color.
 * If you see a teal window, your OpenGL setup is working correctly!
 */

#include <GL/glut.h>
#include <stdio.h>

/*
 * display - Called when the window needs to be redrawn
 * 
 * This function clears the window to a teal color and swaps the buffers
 * to display the result.
 */
void display(void) {
    /* Set clear color to teal (R=0.0, G=0.5, B=0.5, A=1.0) */
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
    
    /* Clear the color buffer and depth buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Swap the front and back buffers (double buffering) */
    glutSwapBuffers();
}

/*
 * main - Entry point
 */
int main(int argc, char** argv) {
    printf("Chapter 2: Hello Window\n");
    printf("=======================\n");
    printf("You should see a teal window.\n");
    printf("Close the window or press Ctrl+C to exit.\n\n");
    
    /* Initialize GLUT */
    glutInit(&argc, argv);
    
    /* Set display mode:
     * GLUT_DOUBLE - Double buffering (smooth animation)
     * GLUT_RGB    - RGB color mode
     * GLUT_DEPTH  - Depth buffer for 3D
     */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    /* Set window size */
    glutInitWindowSize(800, 600);
    
    /* Create window with title */
    glutCreateWindow("Chapter 2: Hello Window");
    
    /* Register callback functions */
    glutDisplayFunc(display);  /* Called when window needs redrawing */
    glutIdleFunc(display);     /* Called when idle (for continuous updates) */
    
    /* Print OpenGL version info */
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
    printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
    
    /* Enter the GLUT main loop (never returns) */
    glutMainLoop();
    
    return 0;
}

