# Chapter 3: Project Skeleton

## Introduction

Now that you can create a simple window, let's organize code into a proper project structure. This chapter shows you how to structure larger OpenGL projects with multiple files and better organization.

## Why Structure Matters

As projects grow, keeping everything in one file becomes unwieldy. A good structure:
- Separates concerns (rendering, input, math, etc.)
- Makes code reusable
- Simplifies debugging
- Enables collaboration
- Scales to larger projects

## Recommended File Layout

```
project/
├── src/              # Source files
│   ├── main.c
│   ├── render.c
│   ├── input.c
│   └── utils.c
├── include/          # Header files
│   ├── render.h
│   ├── input.h
│   └── utils.h
├── assets/           # Resources (textures, models)
│   ├── textures/
│   └── models/
├── build/            # Build artifacts (not committed)
├── Makefile          # Build instructions
├── CMakeLists.txt    # CMake configuration
└── README.md         # Project documentation
```

## The Minimal Project Structure

For our purposes, we'll use a simpler structure:

```
chapter_XX/
├── main.c            # Entry point
├── gl_utils.c/h      # OpenGL helper functions
├── Makefile
├── CMakeLists.txt
└── README.md
```

## Example: Structured "Hello Triangle"

This chapter's example splits code into multiple files:
- `main.c` - Entry point and GLUT setup
- `gl_utils.c/h` - Reusable OpenGL utilities
- `render.c/h` - Rendering code

### Header Guards

Every header file should use header guards to prevent multiple inclusion:

```c
#ifndef RENDER_H
#define RENDER_H

/* Function declarations */
void init_gl(void);
void display(void);

#endif /* RENDER_H */
```

Modern alternative (not C99 standard but widely supported):
```c
#pragma once
```

## Build Systems

### Makefile

**Pros**:
- Simple and direct
- No dependencies
- Fast for small projects

**Cons**:
- Platform-specific
- Manual dependency tracking
- Can get complex

See `Makefile` in this directory for a production-quality example with:
- Automatic dependency generation
- Separate compilation
- Debug/Release builds

### CMake

**Pros**:
- Cross-platform
- Generates native build files
- Handles dependencies well
- Industry standard

**Cons**:
- More verbose
- Learning curve
- Requires CMake installed

See `CMakeLists.txt` for a comprehensive example.

### Visual Studio Projects

**Pros**:
- GUI integration
- Excellent debugger
- IntelliSense

**Cons**:
- Windows-only
- Large project files
- Not version-control friendly

For Visual Studio users: Create a new "Empty Project", add source files, and configure:
1. Project Properties → C/C++ → Additional Include Directories
2. Project Properties → Linker → Additional Library Directories
3. Project Properties → Linker → Input → Additional Dependencies: `opengl32.lib glu32.lib freeglut.lib`

## Code Organization Patterns

### 1. Initialization/Cleanup

```c
void init_gl(void) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    /* More initialization */
}

void cleanup(void) {
    /* Free resources */
}
```

### 2. Callback Functions

Keep callbacks in `main.c` but have them call functions from other modules:

```c
void display(void) {
    render_scene();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    handle_keyboard(key, x, y);
}
```

### 3. Utility Functions

Create helper functions for common tasks:

```c
/* gl_utils.c */
void check_gl_error(const char* context) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error in %s: 0x%x\n", context, err);
    }
}
```

## This Chapter's Example

The example program draws a colored triangle using a structured approach.

### File Breakdown

**main.c**:
- GLUT initialization
- Window creation
- Callback registration
- Main loop

**render.c/h**:
- OpenGL initialization
- Scene rendering
- Drawing functions

**gl_utils.c/h**:
- Error checking
- Debug helpers
- Common utilities

### Building

```bash
# Using Make
make

# Using CMake
mkdir build && cd build
cmake ..
cmake --build .
```

### Running

```bash
./demo
```

You should see a window with a colored triangle.

## Makefile Deep Dive

Our Makefile includes advanced features:

### Automatic Dependency Generation

```makefile
DEPS = $(OBJECTS:.o=.d)
-include $(DEPS)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
```

This automatically tracks which headers each source file includes.

### Debug vs Release

```makefile
# Debug build with symbols
make DEBUG=1

# Release build with optimization
make
```

### Pattern Rules

```makefile
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
```

Automatically compiles any `.c` file to `.o`.

## CMake Deep Dive

### Finding Packages

```cmake
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
```

CMake automatically locates libraries across platforms.

### Build Types

```bash
# Debug build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build
cmake -DCMAKE_BUILD_TYPE=Release ..
```

### Out-of-Source Builds

Always build in a separate directory:
```bash
mkdir build
cd build
cmake ..
```

This keeps source directory clean.

## Best Practices

### 1. Separate Interface from Implementation

- `.h` files: Declarations only
- `.c` files: Implementations

### 2. Use Consistent Naming

```c
/* Functions: verb_noun or module_action */
void render_scene(void);
void input_handle_keyboard(unsigned char key);

/* Variables: noun or adjective_noun */
int window_width;
float camera_angle;
```

### 3. Comment Generously

```c
/*
 * render_scene - Draws the entire 3D scene
 * 
 * This function is called from the display callback. It sets up
 * the camera, clears buffers, and draws all objects.
 */
void render_scene(void);
```

### 4. Handle Errors

```c
if (!init_gl()) {
    fprintf(stderr, "Failed to initialize OpenGL\n");
    exit(1);
}
```

### 5. Use Constants

```c
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE  "My OpenGL App"
```

## Common Project Files

### .gitignore

```
*.o
*.d
demo
build/
```

### README.md

Every project should have a README with:
- What it does
- How to build it
- Dependencies
- How to run it

## Exercises

1. **Add a new module**: Create `math_utils.c/h` with helper functions
2. **Multiple objects**: Extend `render.c` to draw multiple shapes
3. **Configuration**: Add a config file parser to load settings
4. **Debugging**: Add verbose logging with log levels (INFO, WARNING, ERROR)

## What We Learned

- How to structure multi-file C projects
- Makefile and CMake basics
- Header guards and file organization
- Best practices for code organization

## Next Steps

With a solid project structure in place, [Chapter 4](../chapter_04/README.md) dives into GLUT's features: the main loop, callbacks, and event handling.

---

**Files in this chapter**:
- `main.c` - Program entry point
- `render.c/h` - Rendering code
- `gl_utils.c/h` - Utility functions
- `Makefile` - Advanced Makefile with dependencies
- `CMakeLists.txt` - CMake configuration

