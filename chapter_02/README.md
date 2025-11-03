# Chapter 2: Environment Setup

## Introduction

In this chapter, we'll install all the necessary dependencies and create a simple "Hello Window" program to verify that everything works.

## Installing Dependencies

### Linux

#### Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

#### Fedora/RHEL/CentOS

```bash
sudo dnf install gcc make
sudo dnf install mesa-libGLU-devel freeglut-devel
```

#### Arch Linux

```bash
sudo pacman -S base-devel
sudo pacman -S glu freeglut
```

### macOS

**Note**: Apple deprecated OpenGL in macOS 10.14+, but it still works. For production apps, consider Metal or cross-platform solutions.

Using Homebrew:

```bash
brew install freeglut
```

Xcode Command Line Tools (includes OpenGL headers):

```bash
xcode-select --install
```

### Windows

#### Option 1: MinGW-w64 (Recommended for this tutorial)

1. Install [MSYS2](https://www.msys2.org/)
2. Open MSYS2 terminal and run:

```bash
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-freeglut
```

3. Add `C:\msys64\mingw64\bin` to your PATH

#### Option 2: Visual Studio

1. Install [Visual Studio](https://visualstudio.microsoft.com/) (Community Edition is free)
2. Download FreeGLUT binaries from [transmissionzero.co.uk/software/freeglut-devel/](https://www.transmissionzero.co.uk/software/freeglut-devel/)
3. Extract and copy:
   - Headers to your include directory
   - Libraries to your lib directory
   - DLLs to your executable directory

#### Option 3: CMake (Cross-platform)

CMake can handle dependencies across platforms. We'll use this in our examples.

## Why FreeGLUT Instead of Classic GLUT?

**GLUT** (OpenGL Utility Toolkit) is Mark Kilgard's original windowing library, but:
- Last updated in 1998
- Closed source
- No longer maintained

**FreeGLUT** is an open-source replacement that:
- Maintains API compatibility with GLUT
- Adds new features (mouse wheel, window closing callback, etc.)
- Actively maintained
- Cross-platform
- Easy to install

For our purposes, they're interchangeable—code written for GLUT works with FreeGLUT.

## Verifying Your Installation

Let's create a simple program to verify everything works.

### The "Hello Window" Program

This program opens a window and clears it to a color. If you see a teal window, your setup is working!

See `main.c` in this directory for the complete code.

### Building the Program

#### Linux/macOS

```bash
make
./demo
```

#### Windows (MinGW)

```bash
make
demo.exe
```

#### CMake (All Platforms)

```bash
mkdir build
cd build
cmake ..
cmake --build .
./demo  # or demo.exe on Windows
```

## Understanding the Code

Let's break down what `main.c` does:

### 1. Initialize GLUT

```c
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(800, 600);
glutCreateWindow("Chapter 2: Hello Window");
```

- `glutInit` - Initializes GLUT, processes command-line arguments
- `glutInitDisplayMode` - Sets up the display (double buffered, RGB color, depth buffer)
- `glutInitWindowSize` - Sets window dimensions
- `glutCreateWindow` - Creates the window with a title

### 2. Set Up Callbacks

```c
glutDisplayFunc(display);
glutIdleFunc(display);
```

- `glutDisplayFunc` - Called when the window needs to be redrawn
- `glutIdleFunc` - Called continuously when no events are being processed

### 3. The Display Function

```c
void display(void) {
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);  // Teal background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}
```

- `glClearColor` - Sets the clear color (RGBA, values 0.0 to 1.0)
- `glClear` - Clears the specified buffers
- `glutSwapBuffers` - Swaps front and back buffers (double buffering)

### 4. Enter Main Loop

```c
glutMainLoop();
```

This never returns—GLUT handles the event loop forever.

## Expected Output

When you run the program, you should see:
- A window 800x600 pixels
- Filled with a teal color (cyan/turquoise)
- The window title "Chapter 2: Hello Window"

## Troubleshooting

### "Cannot find -lglut" or "Cannot find -lGL"

**Problem**: Linker can't find OpenGL/GLUT libraries.

**Solution**:
- Verify libraries are installed
- Check library paths in Makefile
- On Linux: `ldconfig -p | grep GL` to find libraries

### "GL/glut.h: No such file or directory"

**Problem**: Compiler can't find headers.

**Solution**:
- Verify headers are installed
- Check include paths in Makefile
- On Linux, headers usually in `/usr/include/GL/`

### Window Opens and Immediately Closes

**Problem**: Program crashes or exits immediately.

**Solution**:
- Check for runtime errors
- On Windows, ensure DLLs are in the same directory as .exe
- Run from terminal to see error messages

### Black Window Instead of Teal

**Problem**: OpenGL calls aren't working.

**Solution**:
- Your OpenGL context might not be initializing
- Check graphics drivers are up to date
- Try running with `glutInitDisplayMode(GLUT_RGB)` (no double buffer or depth)

### macOS Warnings About Deprecation

**Problem**: Compiler warnings about deprecated OpenGL.

**Solution**:
- These are expected on macOS
- Add `-Wno-deprecated-declarations` to suppress warnings
- The code will still work

## What We Learned

- How to install OpenGL development tools on major platforms
- The difference between GLUT and FreeGLUT
- How to create a basic GLUT window
- How to verify your OpenGL setup works

## Exercises

1. **Change Colors**: Modify `glClearColor` to display different colors
   - Try red: `(1.0f, 0.0f, 0.0f, 1.0f)`
   - Try white: `(1.0f, 1.0f, 1.0f, 1.0f)`
   - Try your favorite color!

2. **Different Window Sizes**: Change `glutInitWindowSize` to various dimensions

3. **Multiple Windows**: Call `glutCreateWindow` multiple times (each needs its own display callback)

## Next Steps

Now that your environment is working, [Chapter 3](../chapter_03/README.md) will show you how to organize a proper project structure with better build systems.

---

**Files in this chapter**:
- `main.c` - Hello Window program
- `Makefile` - Linux/macOS build file
- `CMakeLists.txt` - Cross-platform build configuration

