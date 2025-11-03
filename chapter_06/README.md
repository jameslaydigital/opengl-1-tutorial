# Chapter 6: Coordinate Systems & the Matrix Stacks

## Introduction

This chapter covers one of the most important concepts in 3D graphics: coordinate transformations. Understanding matrices and coordinate systems is essential for positioning, rotating, and scaling objects.

## Coordinate Systems

### Object Space (Local Space)

Coordinates relative to the object's own origin. For example, a cube centered at its own origin.

### World Space

Coordinates in the global scene. Multiple objects positioned relative to a common origin.

### View Space (Camera/Eye Space)

Coordinates relative to the camera/viewer position.

### Clip Space

Coordinates after projection, before normalization.

### Screen Space

Final 2D pixel coordinates.

## The Two Matrix Stacks

OpenGL 1.1 maintains two main matrix stacks:

### MODELVIEW Matrix

Combines:
- **Model Transform**: Object → World space
- **View Transform**: World → Camera space

Used for positioning objects and the camera.

### PROJECTION Matrix

Defines how 3D coordinates map to 2D screen:
- **Perspective**: Objects further away appear smaller
- **Orthographic**: Parallel lines stay parallel (no perspective)

## Matrix Modes

Switch between matrix stacks:

```c
glMatrixMode(GL_MODELVIEW);
glMatrixMode(GL_PROJECTION);
glMatrixMode(GL_TEXTURE);  /* For texture matrices */
```

Always know which matrix you're modifying!

## The Transformation Pipeline

```
Local Coords → Model Matrix → World Coords
            → View Matrix → Camera Coords
            → Projection Matrix → Clip Coords
            → Perspective Divide → NDC (Normalized Device Coords)
            → Viewport Transform → Screen Coords
```

## Basic Transformations

### glLoadIdentity

Reset to identity matrix (no transformation):

```c
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();  /* Reset transformations */
```

Always start your display function with this.

### glTranslatef - Move Objects

```c
glTranslatef(x, y, z);
```

Example:
```c
glLoadIdentity();
glTranslatef(2.0f, 0.0f, -5.0f);  /* Move right 2, back 5 */
draw_cube();
```

### glRotatef - Rotate Objects

```c
glRotatef(angle_degrees, axis_x, axis_y, axis_z);
```

Examples:
```c
/* Rotate 45° around Z axis */
glRotatef(45.0f, 0.0f, 0.0f, 1.0f);

/* Rotate around Y axis */
glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

/* Rotate around arbitrary axis */
glRotatef(30.0f, 1.0f, 1.0f, 0.0f);
```

### glScalef - Scale Objects

```c
glScalef(sx, sy, sz);
```

Examples:
```c
/* Uniform scale (2x bigger) */
glScalef(2.0f, 2.0f, 2.0f);

/* Non-uniform scale */
glScalef(1.0f, 2.0f, 1.0f);  /* Stretch vertically */

/* Mirror (negative scale) */
glScalef(-1.0f, 1.0f, 1.0f);  /* Flip horizontally */
```

## Order Matters!

Transformations are applied in **reverse order** of calls:

```c
glLoadIdentity();
glTranslatef(5.0f, 0.0f, 0.0f);  /* Second: move right */
glRotatef(45.0f, 0.0f, 0.0f, 1.0f);  /* First: rotate */
draw_square();
```

This rotates the square, **then** moves it right.

Reverse the order:
```c
glLoadIdentity();
glRotatef(45.0f, 0.0f, 0.0f, 1.0f);  /* Second: rotate */
glTranslatef(5.0f, 0.0f, 0.0f);  /* First: move right */
draw_square();
```

This moves it right, **then** rotates it (orbits around origin).

Think: **read bottom to top** or **last to first**.

## Matrix Stack Operations

### glPushMatrix / glPopMatrix

Save and restore the current matrix:

```c
glPushMatrix();  /* Save current matrix */
    glTranslatef(1.0f, 0.0f, 0.0f);
    draw_cube();  /* Draw transformed cube */
glPopMatrix();  /* Restore previous matrix */

draw_sphere();  /* Not affected by translation */
```

Use for:
- Drawing multiple objects independently
- Hierarchical transformations (robot arms, solar systems, etc.)

Example - Solar System:
```c
glPushMatrix();
    glRotatef(orbit_angle, 0, 1, 0);  /* Sun's orbit */
    draw_sun();
    
    glPushMatrix();
        glTranslatef(10.0f, 0, 0);  /* Earth offset */
        glRotatef(earth_angle, 0, 1, 0);  /* Earth's rotation */
        draw_earth();
        
        glPushMatrix();
            glTranslatef(3.0f, 0, 0);  /* Moon offset */
            glRotatef(moon_angle, 0, 1, 0);  /* Moon's rotation */
            draw_moon();
        glPopMatrix();
    glPopMatrix();
glPopMatrix();
```

## Projection Matrices

### Perspective Projection

Objects further away appear smaller (realistic):

```c
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(fovy, aspect, near, far);
```

- `fovy`: Field of view (Y axis) in degrees (typically 45-60)
- `aspect`: Width / Height ratio
- `near`: Near clipping plane (typical: 0.1)
- `far`: Far clipping plane (typical: 100.0)

Example:
```c
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / height, 0.1, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
}
```

### Orthographic Projection

No perspective, parallel lines stay parallel (good for 2D, CAD):

```c
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(left, right, bottom, top, near, far);
```

Example - 2D view:
```c
glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);
```

Example - Aspect-aware 2D:
```c
float aspect = (float)width / height;
if (width >= height) {
    glOrtho(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
} else {
    glOrtho(-1.0, 1.0, -1.0/aspect, 1.0/aspect, -1.0, 1.0);
}
```

### GLU 2D Ortho

Shortcut for 2D orthographic:

```c
gluOrtho2D(left, right, bottom, top);
/* Equivalent to: */
glOrtho(left, right, bottom, top, -1.0, 1.0);
```

## Camera Control with gluLookAt

Position and orient the camera:

```c
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(eye_x, eye_y, eye_z,        /* Camera position */
          center_x, center_y, center_z, /* Look-at point */
          up_x, up_y, up_z);            /* Up vector */
```

Example - Camera looking at origin from above:
```c
gluLookAt(0.0, 5.0, 10.0,   /* Camera at (0, 5, 10) */
          0.0, 0.0, 0.0,    /* Looking at origin */
          0.0, 1.0, 0.0);   /* Y-axis is up */
```

Example - Orbit camera:
```c
float radius = 10.0f;
float angle = time * 0.5f;
float eye_x = radius * cosf(angle);
float eye_z = radius * sinf(angle);

gluLookAt(eye_x, 5.0, eye_z,
          0.0, 0.0, 0.0,
          0.0, 1.0, 0.0);
```

## Understanding the Coordinate System

OpenGL uses a **right-handed** coordinate system:
- **+X**: Right
- **+Y**: Up
- **+Z**: Out of screen (towards you)

When using perspective projection, you typically look down the **-Z** axis (into the screen), so objects need **negative Z** to be visible.

## This Chapter's Example

The example demonstrates:
1. Perspective and orthographic projections
2. All transformation types
3. Matrix push/pop for hierarchies
4. Camera control with gluLookAt
5. Animated solar system
6. Interactive camera

### Controls
- **1-6**: Different demo modes
- **Arrow keys**: Move camera
- **P/O**: Toggle perspective/orthographic
- **ESC**: Quit

## Common Patterns

### Standard 3D Setup

```c
void init_gl(void) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w/h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    /* Position camera */
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
    
    /* Draw objects */
    glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(angle, 0, 1, 0);
        draw_object();
    glPopMatrix();
    
    glutSwapBuffers();
}
```

### Standard 2D Setup

```c
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);  /* Pixel coordinates */
    glMatrixMode(GL_MODELVIEW);
}
```

## Exercises

1. **Rotating Cube**: Draw a cube that rotates continuously
2. **Solar System**: Sun, Earth, Moon with proper orbits
3. **Robot Arm**: Hierarchical transformations (shoulder, elbow, wrist)
4. **FPS Camera**: First-person camera with WASD movement
5. **Zoom**: Implement zoom by changing FOV or moving camera

## What We Learned

- The two matrix stacks (MODELVIEW and PROJECTION)
- Basic transformations (translate, rotate, scale)
- Matrix push/pop for hierarchies
- Perspective vs orthographic projection
- Camera control with gluLookAt
- Transformation order matters

## Next Steps

[Chapter 7](../chapter_07/README.md) covers depth testing, culling, and viewports—essential for correct 3D rendering.

---

**Files in this chapter**:
- `main.c` - Comprehensive transformation examples
- `camera.c/h` - Camera control utilities
- `Makefile` / `CMakeLists.txt` - Build files

