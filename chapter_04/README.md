# Chapter 4: GLUT 101 - Window + Main Loop

## Introduction

GLUT (and FreeGLUT) provides a simple abstraction for creating windows and handling events. This chapter explores GLUT's core features: initialization, display modes, the main loop, and callbacks.

## GLUT Initialization

### glutInit

```c
glutInit(&argc, argv);
```

Must be called before any other GLUT functions. It:
- Initializes the GLUT library
- Processes command-line arguments (like `-display` on X11)
- Sets up internal state

### glutInitDisplayMode

```c
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
```

Configures the framebuffer:

| Flag | Purpose |
|------|---------|
| `GLUT_SINGLE` | Single-buffered (avoid for animation) |
| `GLUT_DOUBLE` | Double-buffered (smooth animation) |
| `GLUT_RGB` | RGB color mode |
| `GLUT_RGBA` | RGB + Alpha |
| `GLUT_INDEX` | Color index mode (legacy) |
| `GLUT_DEPTH` | Depth buffer for 3D |
| `GLUT_STENCIL` | Stencil buffer for masking |
| `GLUT_ACCUM` | Accumulation buffer |
| `GLUT_ALPHA` | Alpha channel |
| `GLUT_MULTISAMPLE` | Multisample anti-aliasing |

Most common: `GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH`

### Window Creation

```c
glutInitWindowSize(800, 600);
glutInitWindowPosition(100, 100);  /* Optional */
int window = glutCreateWindow("Title");
```

- `glutInitWindowSize` - Sets dimensions
- `glutInitWindowPosition` - Sets screen position (optional)
- `glutCreateWindow` - Creates window, returns window ID

## The Main Loop

```c
glutMainLoop();
```

This function:
- Never returns (use `exit()` to quit)
- Processes events (keyboard, mouse, reshape, etc.)
- Calls registered callbacks
- Manages window updates

It's the heart of every GLUT application.

## Double Buffering

### Why Double Buffer?

**Single buffering**: Drawing directly to the visible screen causes flickering as you clear and redraw.

**Double buffering**: 
1. Draw to an off-screen "back buffer"
2. When complete, swap it with the "front buffer" (visible)
3. Instant, smooth updates

### Using Double Buffering

```c
/* In init */
glutInitDisplayMode(GLUT_DOUBLE | ...);

/* In display callback */
void display(void) {
    glClear(...);
    /* Draw stuff */
    glutSwapBuffers();  /* Swap back and front buffers */
}
```

Always use `glutSwapBuffers()` instead of `glFlush()` with double buffering.

## Callbacks

GLUT uses callbacks to handle events. You register functions that GLUT calls when events occur.

### Display Callback (Required)

```c
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Draw your scene */
    glutSwapBuffers();
}

glutDisplayFunc(display);
```

Called when:
- Window needs redrawing
- You call `glutPostRedisplay()`

### Idle Callback

```c
void idle(void) {
    /* Update animation, physics, etc. */
    glutPostRedisplay();  /* Request redraw */
}

glutIdleFunc(idle);
```

Called continuously when no events are being processed. Good for animations but can waste CPU.

### Reshape Callback

```c
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    /* Update projection matrix */
}

glutReshapeFunc(reshape);
```

Called when window is resized. Always update the viewport here.

### Keyboard Callback

```c
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {  /* ESC */
        exit(0);
    }
}

glutKeyboardFunc(keyboard);
```

- `key`: ASCII character
- `x, y`: Mouse position when key was pressed

### Special Keys Callback

```c
void special(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F1:
            /* ... */
            break;
        case GLUT_KEY_UP:
            /* ... */
            break;
    }
}

glutSpecialFunc(special);
```

For arrow keys, function keys, etc.

### Mouse Button Callback

```c
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        /* Left mouse button pressed */
    }
}

glutMouseFunc(mouse);
```

### Mouse Motion Callback

```c
void motion(int x, int y) {
    /* Mouse dragged (button held down) */
}

void passive_motion(int x, int y) {
    /* Mouse moved (no button held) */
}

glutMotionFunc(motion);
glutPassiveMotionFunc(passive_motion);
```

## VSync and Timing

### What is VSync?

**VSync** (Vertical Synchronization) synchronizes your frame rate with the monitor's refresh rate (typically 60 Hz).

**Benefits**:
- Eliminates screen tearing
- Consistent frame timing

**Drawbacks**:
- Caps frame rate at monitor refresh
- Can cause input lag

### Controlling VSync

GLUT doesn't provide direct VSync control. It depends on driver settings:

**Linux (NVIDIA)**:
```bash
__GL_SYNC_TO_VBLANK=1 ./demo
```

**Linux (Mesa)**:
```bash
vblank_mode=1 ./demo
```

**Windows**: Usually controlled by driver settings

**macOS**: Enabled by default

## This Chapter's Example

The example demonstrates:
1. All major callbacks
2. Double buffering
3. Animation in the idle callback
4. Keyboard and mouse interaction
5. Window reshape handling

### Controls

- **Arrow keys**: Move the square
- **Mouse click**: Change color
- **ESC/Q**: Quit
- **F**: Toggle fullscreen
- **R**: Reset position

## Understanding the Event Loop

GLUT's main loop does roughly this:

```c
while (1) {
    /* Process pending events */
    while (events_pending()) {
        event = get_next_event();
        dispatch_callback(event);
    }
    
    /* Call idle callback if registered */
    if (idle_callback) {
        idle_callback();
    }
    
    /* Display if needed */
    if (display_needed) {
        display_callback();
    }
}
```

## Best Practices

### 1. Always Register Display Callback

```c
glutDisplayFunc(display);  /* Required! */
```

### 2. Request Redraws Explicitly

Don't draw outside the display callback:

```c
/* WRONG */
void idle(void) {
    glClear(...);
    draw_scene();
    glutSwapBuffers();
}

/* RIGHT */
void idle(void) {
    update_animation();
    glutPostRedisplay();  /* Request redraw */
}

void display(void) {
    glClear(...);
    draw_scene();
    glutSwapBuffers();
}
```

### 3. Use Timing for Animation

The idle callback runs as fast as possible. For frame-rate-independent animation:

```c
void idle(void) {
    static int last_time = 0;
    int current_time = glutGet(GLUT_ELAPSED_TIME);
    float delta = (current_time - last_time) / 1000.0f;
    
    update_animation(delta);
    
    last_time = current_time;
    glutPostRedisplay();
}
```

### 4. Handle Reshape Properly

```c
void reshape(int width, int height) {
    /* Avoid division by zero */
    height = (height == 0) ? 1 : height;
    
    /* Update viewport */
    glViewport(0, 0, width, height);
    
    /* Update projection (Chapter 6) */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* ... set up projection ... */
    
    glMatrixMode(GL_MODELVIEW);
}
```

## Common Issues

### Window Doesn't Appear

**Problem**: Forgot to call `glutMainLoop()`.

**Solution**: Ensure `glutMainLoop()` is called.

### Window Opens Then Closes

**Problem**: No display callback registered.

**Solution**: Always call `glutDisplayFunc(display)`.

### Flickering Graphics

**Problem**: Using single buffering or not swapping properly.

**Solution**:
```c
glutInitDisplayMode(GLUT_DOUBLE | ...);
/* In display: */
glutSwapBuffers();
```

### Idle Callback Hogging CPU

**Problem**: Idle callback runs continuously at full speed.

**Solution**: Use timer callbacks or add sleep:

```c
void timer(int value) {
    update_animation();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);  /* ~60 FPS */
}

glutTimerFunc(0, timer, 0);
```

## Advanced Features

### Multiple Windows

```c
int window1 = glutCreateWindow("Window 1");
glutDisplayFunc(display1);

int window2 = glutCreateWindow("Window 2");
glutDisplayFunc(display2);

/* Switch between windows */
glutSetWindow(window1);
```

### Fullscreen

```c
glutFullScreen();
glutReshapeWindow(800, 600);  /* Exit fullscreen */
```

### Hide/Show Cursor

```c
glutSetCursor(GLUT_CURSOR_NONE);  /* Hide */
glutSetCursor(GLUT_CURSOR_INHERIT);  /* Show */
```

## Exercises

1. **FPS Counter**: Display frames per second
2. **Color Cycle**: Animate background color
3. **Mouse Trail**: Draw where the mouse has been
4. **Keyboard State**: Track which keys are currently pressed
5. **Smooth Animation**: Implement delta-time-based movement

## What We Learned

- GLUT initialization and display modes
- The main loop and event processing
- Double buffering for smooth animation
- All major callback types
- Best practices for GLUT applications

## Next Steps

Now that you understand GLUT's structure, [Chapter 5](../chapter_05/README.md) will teach you how to actually draw things with immediate mode rendering.

---

**Files in this chapter**:
- `main.c` - Complete GLUT callback demonstration
- `Makefile` - Build configuration
- `CMakeLists.txt` - CMake configuration

