# Chapter 1: What You're Getting Into

## Introduction

Welcome to this OpenGL 1.1 tutorial! This chapter explains what OpenGL 1.1 is, why we're learning it, and what you can expect to accomplish.

## Fixed-Function vs. Modern OpenGL

### The Fixed-Function Pipeline (OpenGL 1.1-2.1)

OpenGL 1.1 uses a **fixed-function pipeline**, where the graphics card follows a predetermined set of steps:

1. **Vertex Transformation** - Transform vertices using built-in matrix stacks
2. **Lighting** - Apply Phong-style lighting automatically
3. **Rasterization** - Convert geometry to pixels
4. **Texturing** - Apply textures using built-in texture units
5. **Fragment Operations** - Depth testing, blending, etc.

You control this pipeline through state changes and built-in functions like `glLight()`, `glMaterial()`, etc.

### Modern OpenGL (3.0+)

Modern OpenGL uses a **programmable pipeline** where you write:
- **Vertex Shaders** - Process each vertex
- **Fragment Shaders** - Process each pixel
- Custom data structures and algorithms

This gives you much more control but has a steeper learning curve.

## Why Learn OpenGL 1.1 in 2025?

### Educational Value

1. **Immediate Results** - Draw a triangle in 10 lines of code
2. **Core Concepts** - Matrices, coordinates, depth, lighting—all transferable
3. **No Shader Complexity** - Focus on graphics concepts, not GLSL syntax
4. **Visual Debugging** - See exactly what each function does

### Practical Reasons

1. **Legacy Codebases** - Many older applications still use it
2. **Embedded Systems** - Some platforms only support OpenGL ES 1.x
3. **Prototyping** - Quick mockups without shader boilerplate
4. **Educational Tools** - Teaching fundamental graphics concepts

## "Deprecated but Useful"

OpenGL 1.1 was officially deprecated in OpenGL 3.0 (2008), but:
- It still works on modern hardware (through compatibility contexts)
- Drivers maintain support for backward compatibility
- It's excellent for learning fundamentals
- Concepts translate directly to modern APIs

**Important**: We're not suggesting you use this for production software. We're using it as a teaching tool.

## What We'll Build

Throughout this tutorial, you'll create:

1. **Simple Shapes** - Triangles, quads, circles
2. **3D Objects** - Cubes, spheres, custom meshes
3. **Lit Scenes** - Multiple light sources with materials
4. **Textured Models** - Load and apply images
5. **Interactive Demos** - Camera controls, animations
6. **Complete Projects** - Particle systems, terrain rendering

## Platform Support

### Where It Runs Well

- **Windows** - Full support, all drivers
- **Linux** - Excellent support with Mesa and proprietary drivers
- **macOS** - Works but deprecated (OpenGL frozen at 4.1)

### Limitations

- **macOS** - Apple deprecated OpenGL in favor of Metal
- **WebGL** - Based on OpenGL ES, not desktop GL 1.1
- **Mobile** - Uses OpenGL ES, which has a different API

## The Learning Path

This tutorial follows a structured path:

1. **Setup** (Chapters 2-3) - Get your environment ready
2. **Basics** (Chapters 4-7) - Windows, drawing, coordinates
3. **Advanced Features** (Chapters 8-12) - Lighting, textures, optimization
4. **Polish** (Chapters 13-14) - Input, UI, text
5. **Production** (Chapters 15-19) - Debugging, performance, deployment
6. **Practice** (Chapter 20) - Hands-on projects
7. **Next Steps** (Chapter 21) - Moving to modern OpenGL

## Prerequisites

To get the most out of this tutorial, you should:

- **Know C** - Pointers, structs, basic memory management
- **Have patience** - Graphics programming has many moving parts
- **Be willing to experiment** - Change values, break things, learn

You don't need to know:
- Advanced math (we'll explain as we go)
- Graphics theory (we'll teach it)
- Other graphics APIs

## What to Expect

### Time Investment

- **Casual pace**: 2-3 hours per chapter
- **Full tutorial**: 40-60 hours of learning
- **Practice projects**: Additional 20-40 hours

### Difficulty Curve

- Chapters 1-7: Gentle introduction
- Chapters 8-12: Moderate complexity
- Chapters 13-21: Advanced topics

## Tools and Resources

### What You'll Need

- A text editor or IDE (VSCode, Vim, Visual Studio, etc.)
- C compiler (GCC, Clang, or MSVC)
- FreeGLUT library
- OpenGL headers (usually bundled with graphics drivers)

### Optional but Helpful

- Graphics debugger (RenderDoc, apitrace)
- Math library for advanced projects
- Image editing software for creating textures

## Setting Expectations

### What This Tutorial Is

✓ Comprehensive coverage of OpenGL 1.1
✓ Working code examples for every concept
✓ Practical exercises and projects
✓ Bridge to modern OpenGL concepts

### What This Tutorial Isn't

✗ Production-ready application development
✗ Modern OpenGL 3.3+ with shaders
✗ Game engine development
✗ Advanced mathematical graphics theory

## Next Steps

In the next chapter, we'll set up your development environment and verify that everything works with a simple "Hello Window" program.

## Additional Reading

- **OpenGL 1.1 Specification** - The official reference (available on khronos.org)
- **Red Book** (early editions) - The classic OpenGL Programming Guide
- **NeHe Productions** - Classic OpenGL tutorials (legacy but valuable)

---

**Ready to continue?** Head to [Chapter 2: Environment Setup](../chapter_02/README.md)

