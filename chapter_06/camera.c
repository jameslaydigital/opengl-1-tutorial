/*
 * camera.c - Simple camera implementation
 */

#include <GL/glu.h>
#include <math.h>
#include "camera.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void camera_init(camera_t* cam) {
    cam->angle_h = 45.0f;
    cam->angle_v = 30.0f;
    cam->distance = 10.0f;
}

void camera_apply(camera_t* cam) {
    /* Convert angles to radians */
    float h_rad = cam->angle_h * M_PI / 180.0f;
    float v_rad = cam->angle_v * M_PI / 180.0f;
    
    /* Calculate camera position */
    float eye_x = cam->distance * cosf(v_rad) * sinf(h_rad);
    float eye_y = cam->distance * sinf(v_rad);
    float eye_z = cam->distance * cosf(v_rad) * cosf(h_rad);
    
    /* Look at origin */
    gluLookAt(eye_x, eye_y, eye_z,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
}

