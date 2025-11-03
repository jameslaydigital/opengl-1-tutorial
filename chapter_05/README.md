# Chapter 5: Drawing in Immediate Mode

## Introduction

Now it's time to actually draw things! This chapter covers OpenGL 1.1's immediate mode rendering: `glBegin`/`glEnd`, primitives, colors, and the state machine.

## The OpenGL State Machine

OpenGL is a **state machine**. You set states (colors, line width, etc.), and they remain active until you change them:

```c
glColor3f(1.0f, 0.0f, 0.0f);  /* Set color to red */
draw_triangle();               /* Drawn in red */
draw_square();                 /* Also red! */
```

Think of it like a painting: you select a brush color, and everything you paint uses that color until you pick a different one.

## Clearing the Screen

### glClearColor

Sets the color used when clearing:

```c
glClearColor(0.2f, 0.3f, 0.4f, 1.0f);  /* RGBA, values 0.0 to 1.0 */
```

### glClear

Clears specified buffers:

```c
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

- `GL_COLOR_BUFFER_BIT` - Clear color
- `GL_DEPTH_BUFFER_BIT` - Clear depth (essential for 3D)
- `GL_STENCIL_BUFFER_BIT` - Clear stencil
- `GL_ACCUM_BUFFER_BIT` - Clear accumulation buffer

Always clear at the beginning of your display function.

## Immediate Mode Rendering

### The glBegin/glEnd Pattern

```c
glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
glEnd();
```

Between `glBegin` and `glEnd`:
- Specify vertices with `glVertex*`
- Set per-vertex attributes (color, texture coordinates, normals)
- No state changes allowed (no `glEnable`, `glDisable`, etc.)

## Primitives

OpenGL supports various primitive types:

### GL_POINTS

Individual points:

```c
glBegin(GL_POINTS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.5f, 0.5f);
glEnd();
```

Use `glPointSize(size)` to change point size.

### GL_LINES

Line segments (2 vertices per line):

```c
glBegin(GL_LINES);
    glVertex2f(-0.5f, 0.0f);  /* Line 1 start */
    glVertex2f(0.5f, 0.0f);   /* Line 1 end */
    glVertex2f(0.0f, -0.5f);  /* Line 2 start */
    glVertex2f(0.0f, 0.5f);   /* Line 2 end */
glEnd();
```

### GL_LINE_STRIP

Connected lines:

```c
glBegin(GL_LINE_STRIP);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    /* Creates 2 connected lines */
glEnd();
```

### GL_LINE_LOOP

Like `GL_LINE_STRIP`, but connects last vertex to first:

```c
glBegin(GL_LINE_LOOP);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    /* Creates a square outline */
glEnd();
```

### GL_TRIANGLES

Independent triangles (3 vertices each):

```c
glBegin(GL_TRIANGLES);
    /* Triangle 1 */
    glVertex2f(0.0f, 0.5f);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    
    /* Triangle 2 */
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.5f, 0.0f);
    glVertex2f(0.0f, -0.5f);
glEnd();
```

### GL_TRIANGLE_STRIP

Efficient for connected triangles:

```c
glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(-0.5f, 0.5f);   /* v0 */
    glVertex2f(-0.5f, -0.5f);  /* v1 */
    glVertex2f(0.5f, 0.5f);    /* v2: triangle v0-v1-v2 */
    glVertex2f(0.5f, -0.5f);   /* v3: triangle v1-v3-v2 */
glEnd();
```

Each new vertex creates a triangle with the previous two.

### GL_TRIANGLE_FAN

Triangles sharing a common vertex:

```c
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);    /* Center */
    glVertex2f(0.5f, 0.0f);
    glVertex2f(0.4f, 0.3f);
    glVertex2f(0.0f, 0.5f);
    /* ... more vertices ... */
glEnd();
```

### GL_QUADS

Quadrilaterals (4 vertices each):

```c
glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
glEnd();
```

**Note**: Quads were removed in OpenGL 3.0+. Use triangles for compatibility.

### GL_QUAD_STRIP

Similar to triangle strip, but for quads.

### GL_POLYGON

Convex polygon (any number of vertices):

```c
glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(-0.3f, -0.5f);
    glVertex2f(0.3f, -0.5f);
    glVertex2f(0.5f, 0.0f);
glEnd();
```

**Limitation**: Only works for **convex** polygons. For concave, use tessellation or triangulation.

## Vertex Functions

OpenGL provides overloaded vertex functions:

```c
/* 2D */
glVertex2f(x, y);
glVertex2d(x, y);         /* Double precision */
glVertex2i(x, y);         /* Integer */

/* 3D */
glVertex3f(x, y, z);

/* 4D (homogeneous) */
glVertex4f(x, y, z, w);

/* Array versions */
float vertex[3] = {x, y, z};
glVertex3fv(vertex);
```

Most common: `glVertex2f` (2D) and `glVertex3f` (3D).

## Colors

### Setting Colors

```c
/* RGB */
glColor3f(1.0f, 0.0f, 0.0f);  /* Red */

/* RGBA */
glColor4f(1.0f, 0.0f, 0.0f, 0.5f);  /* Semi-transparent red */

/* Byte versions (0-255) */
glColor3ub(255, 0, 0);

/* Array versions */
float color[3] = {1.0f, 0.0f, 0.0f};
glColor3fv(color);
```

### Per-Vertex Colors (Smooth Shading)

You can set a different color for each vertex:

```c
glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);  /* Red */
    glVertex2f(0.0f, 0.5f);
    
    glColor3f(0.0f, 1.0f, 0.0f);  /* Green */
    glVertex2f(-0.5f, -0.5f);
    
    glColor3f(0.0f, 0.0f, 1.0f);  /* Blue */
    glVertex2f(0.5f, -0.5f);
glEnd();
```

Colors are **interpolated** across the triangle (gradient effect).

### Shading Models

```c
glShadeModel(GL_SMOOTH);  /* Interpolate colors (default) */
glShadeModel(GL_FLAT);    /* Use color of first vertex for entire primitive */
```

## Common State Functions

### Line Width

```c
glLineWidth(2.5f);  /* Width in pixels */
```

### Point Size

```c
glPointSize(10.0f);  /* Diameter in pixels */
```

### Polygon Mode

```c
/* Fill polygons (default) */
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

/* Draw outlines only */
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

/* Draw points only */
glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
```

Great for debugging geometry.

## This Chapter's Example

The example demonstrates:
1. All primitive types
2. Per-vertex colors
3. Smooth vs flat shading
4. Line width and point size
5. Polygon modes

Use number keys to switch between different examples.

## Drawing Circles

OpenGL doesn't have a circle primitive, but you can approximate one:

```c
void draw_circle(float cx, float cy, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);  /* Center */
        
        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * M_PI * i / segments;
            float x = cx + radius * cosf(angle);
            float y = cy + radius * sinf(angle);
            glVertex2f(x, y);
        }
    glEnd();
}
```

For an outline:

```c
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
```

## Best Practices

### 1. Group Primitives

```c
/* INEFFICIENT: Multiple glBegin/glEnd calls */
for (int i = 0; i < 100; i++) {
    glBegin(GL_TRIANGLES);
        draw_triangle(i);
    glEnd();
}

/* BETTER: One glBegin/glEnd call */
glBegin(GL_TRIANGLES);
    for (int i = 0; i < 100; i++) {
        draw_triangle_vertices(i);
    }
glEnd();
```

### 2. Use Appropriate Primitives

- Use `GL_TRIANGLE_STRIP` for meshes
- Use `GL_LINE_LOOP` for closed shapes
- Avoid `GL_POLYGON` for complex shapes

### 3. Set State Once

```c
/* INEFFICIENT */
glColor3f(1.0f, 0.0f, 0.0f);
glBegin(GL_TRIANGLES);
    glVertex2f(...);
    glVertex2f(...);
    glVertex2f(...);
glEnd();

/* SAME RESULT */
glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(...);
    glVertex2f(...);
    glVertex2f(...);
glEnd();
```

Both work, but setting color outside is clearer when all vertices use the same color.

## Common Issues

### Nothing Draws

**Possible causes**:
1. Vertices outside viewport
2. Wrong winding order (culling enabled)
3. Color same as background
4. Depth testing issues (clear depth buffer!)

### Colors Look Wrong

**Possible causes**:
1. Lighting enabled (we haven't covered that yet)
2. Wrong color format (check RGB vs RGBA)
3. Previous state not reset

### Lines or Points Too Small

```c
glLineWidth(2.0f);
glPointSize(5.0f);
```

## Performance Notes

Immediate mode is **slow**:
- CPU sends each vertex individually
- High function call overhead
- No GPU-side caching

For better performance:
- Use vertex arrays (Chapter 12)
- Use display lists (Chapter 11)
- Modern GL: use VBOs

However, immediate mode is perfect for:
- Learning
- Prototyping
- Debug visualization
- Small amounts of geometry

## Exercises

1. **Star**: Draw a 5-pointed star
2. **Checkerboard**: Draw an 8x8 grid of alternating colors
3. **Rainbow**: Draw a gradient with smooth color transitions
4. **Spiral**: Draw a spiral using lines
5. **Analog Clock**: Draw clock face with hands

## What We Learned

- OpenGL's state machine model
- Immediate mode rendering with `glBegin`/`glEnd`
- All primitive types
- Vertex and color functions
- Smooth vs flat shading
- Common rendering states

## Next Steps

[Chapter 6](../chapter_06/README.md) introduces coordinate systems and transformations—essential for positioning and moving objects in 3D space.

---

**Files in this chapter**:
- `main.c` - Complete immediate mode examples
- `primitives.c/h` - Helper functions for drawing shapes
- `Makefile` - Build configuration
- `CMakeLists.txt` - CMake configuration

