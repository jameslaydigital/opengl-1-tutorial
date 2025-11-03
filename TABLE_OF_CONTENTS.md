# Table of Contents

1. **What You’re Getting Into**

   * Fixed-function mindset vs. modern GL (why 1.1 is “deprecated but useful”)
   * What we’ll build and run on

2. **Environment Setup**

   * Installing headers/libs: Windows (MSVC/MinGW), Linux, macOS (notes on deprecation)
   * Getting **FreeGLUT** (and why, instead of classic GLUT)
   * Verifying your toolchain with a tiny “hello window”

3. **Project Skeleton**

   * File layout, minimal `main.c`
   * Makefile/CMake and MSVC project hints

4. **GLUT 101: Window + Main Loop**

   * `glutInit`, display modes, double buffering
   * The display callback, idle, reshape, keyboard/mouse
   * Swap buffers and why VSync matters

5. **Drawing in Immediate Mode**

   * Clearing and the state machine (`glClearColor`, `glClear`, enables)
   * `glBegin`/`glEnd`, primitives, `glVertex*`
   * Colors with `glColor*` and smooth shading

6. **Coordinate Systems & the Matrix Stacks**

   * MODELVIEW vs. PROJECTION
   * `glMatrixMode`, `glLoadIdentity`, `glTranslate/Rotate/Scale`
   * Perspective vs. orthographic with GLU (`gluPerspective`, `glOrtho`)
   * Camera convenience (`gluLookAt`)

7. **Depth, Culling, and Viewport**

   * Enabling depth testing, depth func
   * Backface culling and winding order
   * Resizing the viewport in the reshape callback

8. **Lighting and Materials (Classic Phong-ish)**

   * Enabling `GL_LIGHTING`, ambient/diffuse/specular
   * Light sources (`GL_LIGHT0`…), position vs. direction
   * `glMaterial*`, normals, and `glNormal*`
   * Per-vertex color vs. materials (`glColorMaterial`)

9. **Textures in 1.1**

   * Texture objects (`glGenTextures`, `glBindTexture`)
   * Uploading pixels with `glTexImage2D`, formats, alignment
   * Sampler params (wrap/filter), mipmaps (gluBuild2DMipmaps)
   * Texture coordinates (`glTexCoord*`) and matrix
   * Simple image loader strategy (TGA/PPM or stb_image)

10. **State You’ll Use a Lot**

    * Blending (`glEnable(GL_BLEND)`, blend funcs), alpha
    * Fog (because it’s 1.1 and we can)
    * Polygon mode, line width, point size

11. **Display Lists**

    * What they are, when they help
    * Creating, calling, and deleting lists
    * Limitations and gotchas

12. **Vertex Arrays (the good part of 1.1)**

    * Why arrays beat immediate mode
    * Enabling client states, `glVertexPointer`, `glNormalPointer`, `glTexCoordPointer`
    * Drawing with `glDrawArrays` / `glDrawElements`
    * Interleaved layouts

13. **Input & Interaction with GLUT**

    * Keyboard, special keys, mouse buttons, motion, wheel
    * Simple camera controls (orbit/pan/zoom)
    * Timing & animation (idle vs. timer)

14. **Text & UI Bits**

    * GLUT bitmap and stroke fonts (quick labels, FPS counter)
    * Overlaying 2D HUD with an ortho pass

15. **Common Pitfalls**

    * “Why is everything black?” (normals, lighting, enabling states)
    * Z-fighting, near/far planes, precision
    * Texture looks blurry/blocked? (filters, mipmaps, UNPACK_ALIGNMENT)

16. **Performance Tips for 1.1**

    * Minimize state changes and bind calls
    * Prefer vertex arrays over immediate mode
    * Use display lists for static geometry

17. **Debugging & Introspection**

    * Checking errors with `glGetError` (and a helper macro)
    * Dumping caps/limits with `glGet*`
    * Visual checks: draw normals, bounding boxes

18. **Cross-Platform Notes**

    * Windows (WGL) basics you don’t want to think about
    * Linux (GLX) note—GLUT hides most of it
    * macOS reality: legacy support and workarounds

19. **Packaging a Demo**

    * Static vs. dynamic linking pitfalls
    * Asset paths and working directories
    * Reproducible builds

20. **Exercises & Mini-Projects**

    * Spinning lit cube (immediate mode)
    * Textured cube (mipmaps + filtering comparison)
    * Teapot showcase (lighting/material presets)
    * Particle-style points with blending
    * Vertex-array terrain from a heightmap

21. **Where to Go Next**

    * From fixed-function to modern GL (VBOs/VAOs/shaders at a glance)
    * SDL/GLFW alternatives to GLUT
    * Pointers to modern resources and a migration map
