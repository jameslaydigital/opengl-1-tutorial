# OpenGL 1.1 Tutorial with FreeGLUT

A comprehensive, hands-on tutorial for learning OpenGL 1.1 (fixed-function pipeline) using FreeGLUT. Each chapter includes detailed explanations and working code examples that you can compile and run.

## Why OpenGL 1.1?

While OpenGL 1.1 is considered legacy, it provides:
- An excellent foundation for understanding 3D graphics concepts
- Immediate results without complex shader programming
- Cross-platform compatibility with minimal dependencies
- A gentle learning curve for graphics programming beginners

## Prerequisites

Before starting, you'll need:
- Basic C programming knowledge
- A C compiler (GCC, Clang, or MSVC)
- OpenGL development headers
- FreeGLUT library

## Repository Structure

Each chapter is contained in its own directory with:
- `README.md` - Chapter content and explanations
- Source code files (`.c` and `.h`)
- `Makefile` - Build instructions for Linux/macOS
- `CMakeLists.txt` - Cross-platform build configuration

## Chapters

1. **What You're Getting Into** - Introduction to fixed-function vs. modern OpenGL
2. **Environment Setup** - Installing dependencies and verifying your toolchain
3. **Project Skeleton** - Basic project structure and build systems
4. **GLUT 101: Window + Main Loop** - Creating windows and handling the main loop
5. **Drawing in Immediate Mode** - First rendering with glBegin/glEnd
6. **Coordinate Systems & the Matrix Stacks** - Understanding transformations
7. **Depth, Culling, and Viewport** - Making 3D graphics work correctly
8. **Lighting and Materials** - Classic Phong lighting model
9. **Textures in 1.1** - Loading and applying textures
10. **State You'll Use a Lot** - Blending, fog, and other common states
11. **Display Lists** - Optimizing static geometry
12. **Vertex Arrays** - Better performance than immediate mode
13. **Input & Interaction with GLUT** - Keyboard, mouse, and camera controls
14. **Text & UI Bits** - Drawing text and 2D overlays
15. **Common Pitfalls** - Debugging common issues
16. **Performance Tips for 1.1** - Optimization techniques
17. **Debugging & Introspection** - Tools and techniques for debugging
18. **Cross-Platform Notes** - Platform-specific considerations
19. **Packaging a Demo** - Building distributable applications
20. **Exercises & Mini-Projects** - Practice projects
21. **Where to Go Next** - Transitioning to modern OpenGL
22. **🎮 Final Project: Cosmic Defender** - Complete 3D space shooter game!

## The Final Project

**Chapter 22** is a complete, playable 3D space shooter that demonstrates **every technique** from the tutorial:
- 3D rendering with lighting and materials
- Player movement and camera controls
- Enemy AI with pathfinding
- Projectile physics and collision detection
- Particle effects for explosions
- HUD with health, score, and game states
- Wave-based difficulty progression

**Build and play:**
```bash
cd chapter_22
make
./game
```

This is your capstone project—a real game built with OpenGL 1.1!

## Quick Start

### Linux/macOS

Install dependencies:
```bash
# Ubuntu/Debian
sudo apt-get install build-essential libglu1-mesa-dev freeglut3-dev

# Fedora/RHEL
sudo dnf install gcc make mesa-libGLU-devel freeglut-devel

# macOS (note: OpenGL is deprecated but still works)
brew install freeglut
```

Build and run a chapter:
```bash
cd chapter_02_environment_setup
make
./demo
```

### Windows

Install MinGW-w64 or use MSVC, then install FreeGLUT. Each chapter includes detailed build instructions.

Alternatively, use CMake for cross-platform builds:
```bash
cd chapter_XX
mkdir build && cd build
cmake ..
cmake --build .
```

## Learning Path

- **Beginners**: Follow chapters 1-7 in order
- **Intermediate**: Chapters 8-14 build on the basics
- **Advanced**: Chapters 15-21 cover optimization and best practices
- **Final Project**: Chapter 22 - Build a complete game!

## Contributing

Found a bug or want to improve an example? Pull requests are welcome!

## License

This tutorial and all example code are released into the public domain (or MIT License where public domain is not applicable).

## Acknowledgments

This tutorial is designed to teach OpenGL 1.1 concepts that remain relevant for understanding modern graphics programming, even though the API itself is considered legacy.


## Note for WSL users

I wrote all of these in wsl2, using XWinrc and the following config that I run from my windows desktop:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<XLaunch
    WindowMode="MultiWindow"
    ClientMode="NoClient"
    LocalClient="False"
    Display="0"
    LocalProgram="xcalc"
    RemoteProgram="xterm"
    RemotePassword=""
    PrivateKey=""
    RemoteHost=""
    RemoteUser=""
    XDMCPHost=""
    XDMCPBroadcast="False"
    XDMCPIndirect="False"
    Clipboard="True"
    ClipboardPrimary="True"
    ExtraParams=""
    Wgl="True"
    DisableAC="True"
    XDMCPTerminate="False"
/>
```

Then, in my `.bashrc`, I added:

```bash
export DISPLAY=$(ip route list default | awk '{print $3}'):0
```

Some have recommended `export LIBGL_ALWAYS_INDIRECT=1`, but I would highly
advise against it - I cannot get things to run with a decent framerate if I
enable this setting.
