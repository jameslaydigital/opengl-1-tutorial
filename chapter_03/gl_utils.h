/*
 * gl_utils.h - OpenGL utility functions
 */

#ifndef GL_UTILS_H
#define GL_UTILS_H

/*
 * check_gl_error - Check for OpenGL errors and print them
 * 
 * @context: Description of where the check is happening
 */
void check_gl_error(const char* context);

/*
 * print_gl_info - Print OpenGL version and driver information
 */
void print_gl_info(void);

#endif /* GL_UTILS_H */

