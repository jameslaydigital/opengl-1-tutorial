# Chapter 7: Depth, Culling, and Viewport

## Introduction

This chapter covers essential features for correct 3D rendering: depth testing (Z-buffer), backface culling, and viewport management.

## Depth Testing

### The Z-Buffer Problem

Without depth testing, objects are drawn in the order you specify them, not by distance:

```c
/* Without depth test */
draw_cube_at(0, 0, -10);  /* Far away */
draw_cube_at(0, 0, -5);   /* Closer */
/* Result: Second cube appears in front, regardless of overlap */
```

This works, but only if you carefully sort your geometry (which is impractical for complex scenes).

### Enabling Depth Testing

```c
glEnable(GL_DEPTH_TEST);
```

Now OpenGL tracks depth for each pixel and only draws if the new fragment is closer than what's already there.

### Clearing the Depth Buffer

Always clear the depth buffer each frame:

```c
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

### Depth Function

Control how depth comparison works:

```c
glDepthFunc(GL_LESS);     /* Default: draw if closer */
glDepthFunc(GL_LEQUAL);   /* Draw if closer or equal */
glDepthFunc(GL_GREATER);  /* Draw if farther (unusual) */
glDepthFunc(GL_ALWAYS);   /* Always draw (ignores depth) */
glDepthFunc(GL_NEVER);    /* Never draw */
```

Most common: `GL_LESS` (default) or `GL_LEQUAL`.

### Depth Mask

Control whether depth writes occur:

```c
glDepthMask(GL_FALSE);  /* Disable depth writes (but still test) */
glDepthMask(GL_TRUE);   /* Enable depth writes (default) */
```

Useful for transparent objects (Chapter 10).

## Backface Culling

### What is Backface Culling?

For closed objects (like a cube or sphere), you never see the "inside" faces. Backface culling automatically skips rendering these faces, improving performance.

### Enabling Culling

```c
glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);    /* Cull back faces (default) */
glCullFace(GL_FRONT);   /* Cull front faces (unusual) */
glCullFace(GL_FRONT_AND_BACK);  /* Cull everything (why?) */
```

### Winding Order

OpenGL determines which face is "front" based on vertex order:

**Counter-Clockwise (CCW)** - Front face (default):
```c
glFrontFace(GL_CCW);  /* Default */

/* Front-facing quad */
glBegin(GL_QUADS);
    glVertex3f(-1, -1, 0);  /* Bottom-left */
    glVertex3f( 1, -1, 0);  /* Bottom-right */
    glVertex3f( 1,  1, 0);  /* Top-right */
    glVertex3f(-1,  1, 0);  /* Top-left */
glEnd();
```

**Clockwise (CW)** - Back face:
```c
/* Back-facing quad (will be culled) */
glBegin(GL_QUADS);
    glVertex3f(-1, -1, 0);
    glVertex3f(-1,  1, 0);
    glVertex3f( 1,  1, 0);
    glVertex3f( 1, -1, 0);
glEnd();
```

Change winding direction:
```c
glFrontFace(GL_CW);   /* Clockwise is front */
glFrontFace(GL_CCW);  /* Counter-clockwise is front (default) */
```

### When NOT to Use Culling

- Open surfaces (planes, ribbons)
- Transparent or wireframe objects
- When you want to see both sides
- Two-sided materials (like paper)

## Viewport

### What is the Viewport?

The viewport defines the rectangular region of the window where OpenGL renders. Typically, this is the entire window, but you can render to sub-regions.

### Setting the Viewport

```c
glViewport(x, y, width, height);
```

- `x, y`: Lower-left corner (in pixels)
- `width, height`: Dimensions (in pixels)

Example - Full window:
```c
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    /* Update projection too */
}
```

### Multiple Viewports

You can render the same scene from different angles:

```c
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Left viewport - front view */
    glViewport(0, 0, width/2, height);
    setup_front_camera();
    draw_scene();
    
    /* Right viewport - top view */
    glViewport(width/2, 0, width/2, height);
    setup_top_camera();
    draw_scene();
}
```

### Viewport Aspect Ratio

Always match your projection's aspect ratio to your viewport:

```c
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aspect = (float)w / h;  /* Match viewport! */
    gluPerspective(45.0, aspect, 0.1, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
}
```

Mismatched aspect ratios cause distortion (circles become ovals).

## Scissor Test

Restricts rendering to a rectangular region (like viewport, but discards fragments outside):

```c
glEnable(GL_SCISSOR_TEST);
glScissor(x, y, width, height);

/* Rendering is clipped to scissor region */

glDisable(GL_SCISSOR_TEST);
```

Difference from viewport:
- **Viewport**: Transforms coordinates
- **Scissor**: Clips fragments (faster)

## Common Patterns

### Standard 3D Setup

```c
void init_gl(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);
}
```

### Standard Reshape

```c
void reshape(int w, int h) {
    h = (h == 0) ? 1 : h;  /* Prevent division by zero */
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / h, 0.1, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
}
```

### Standard Display

```c
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
    
    /* Draw objects */
    
    glutSwapBuffers();
}
```

## This Chapter's Example

The example demonstrates:
1. Depth testing on/off comparison
2. Backface culling effects
3. Winding order visualization
4. Split-screen viewports
5. Z-fighting demonstration

### Controls
- **D**: Toggle depth testing
- **C**: Toggle culling
- **W**: Toggle wireframe
- **1-4**: Different demo modes
- **ESC**: Quit

## Common Issues

### Objects Render in Wrong Order

**Problem**: Forgot to enable depth testing.

**Solution**:
```c
glEnable(GL_DEPTH_TEST);
/* AND clear depth buffer each frame: */
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

### Everything is Black/Missing

**Problem**: Culling is on, but vertices are in wrong order.

**Solution**: Either:
1. Fix vertex winding order
2. Disable culling: `glDisable(GL_CULL_FACE);`
3. Change front face: `glFrontFace(GL_CW);`

### Z-Fighting (Flickering)

**Problem**: Two surfaces at the same depth fight for visibility.

**Solution**:
1. Separate surfaces slightly
2. Increase depth buffer precision (request 24-bit depth)
3. Adjust near/far planes (don't use huge range like 0.001 to 10000)
4. Use polygon offset (Chapter 15)

### Distorted Rendering

**Problem**: Aspect ratio mismatch between viewport and projection.

**Solution**: Always compute aspect from viewport dimensions:
```c
float aspect = (float)viewport_width / viewport_height;
gluPerspective(fov, aspect, near, far);
```

## Depth Buffer Precision

The depth buffer has limited precision (typically 16, 24, or 32 bits). Precision is **not uniform**:

- More precision near the near plane
- Less precision at far plane

### Choosing Near/Far Planes

```c
/* BAD: Huge range, poor precision */
gluPerspective(45.0, aspect, 0.001, 10000.0);

/* GOOD: Reasonable range */
gluPerspective(45.0, aspect, 0.1, 100.0);
```

**Rule of thumb**: Keep `far / near` ratio under 1000:1.

## Advanced: Depth Range

Remap depth buffer range:

```c
glDepthRange(near_val, far_val);  /* Values 0.0 to 1.0 */
```

Default: `glDepthRange(0.0, 1.0)`.

Use case: Render UI with `glDepthRange(0.0, 0.1)` to ensure it's always in front.

## Exercises

1. **Depth Test Demo**: Toggle depth test on/off with overlapping objects
2. **Culling Visualizer**: Show front and back faces in different colors
3. **Split Screen**: Render same scene from 4 viewports
4. **Z-Fighting**: Demonstrate and fix z-fighting
5. **Aspect Ratio**: Show distortion from wrong aspect ratio

## Performance Tips

1. **Enable culling**: ~50% performance boost for closed objects
2. **Enable depth test**: Always use it for 3D
3. **Clear both buffers**: Color and depth, every frame
4. **Avoid depth writes for transparent objects**: Use `glDepthMask(GL_FALSE)`

## What We Learned

- Depth testing and the Z-buffer
- Backface culling and winding order
- Viewport management
- Common 3D rendering setup
- Z-fighting and depth precision

## Next Steps

[Chapter 8](../chapter_08/README.md) introduces lighting and materials—bringing your 3D scenes to life with realistic shading.

---

**Files in this chapter**:
- `main.c` - Depth, culling, and viewport demonstrations
- `Makefile` / `CMakeLists.txt` - Build files

