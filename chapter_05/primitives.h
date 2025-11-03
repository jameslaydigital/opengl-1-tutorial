/*
 * primitives.h - Helper functions for drawing shapes
 */

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

void draw_circle(float cx, float cy, float radius, int segments);
void draw_circle_outline(float cx, float cy, float radius, int segments);
void draw_hexagon(float cx, float cy, float radius);
void draw_star(float cx, float cy, float outer_radius, float inner_radius, int points);

#endif /* PRIMITIVES_H */

