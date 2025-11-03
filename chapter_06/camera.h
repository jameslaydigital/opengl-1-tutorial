/*
 * camera.h - Simple camera utilities
 */

#ifndef CAMERA_H
#define CAMERA_H

typedef struct {
    float angle_h;    /* Horizontal angle */
    float angle_v;    /* Vertical angle */
    float distance;   /* Distance from origin */
} camera_t;

void camera_init(camera_t* cam);
void camera_apply(camera_t* cam);

#endif /* CAMERA_H */

