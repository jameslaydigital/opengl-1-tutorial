# Chapter 8: Lighting and Materials (Classic Phong-ish)

## Introduction

This chapter covers OpenGL 1.1's fixed-function lighting model, which provides automatic shading based on light positions, material properties, and surface normals. This is the classic **Phong illumination model**.

## The Phong Lighting Model

The Phong model combines three lighting components:

1. **Ambient** - Constant illumination (simulates indirect light)
2. **Diffuse** - Direction-dependent (Lambert shading)
3. **Specular** - Shiny highlights (view-dependent)

Formula: `Final Color = Ambient + Diffuse + Specular + Emissive`

## Enabling Lighting

```c
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);  /* Enable first light source */
```

OpenGL supports up to 8 lights: `GL_LIGHT0` through `GL_LIGHT7`.

**Important**: Once lighting is enabled, `glColor*` is ignored! Use materials instead.

## Light Sources

### Light Position

```c
GLfloat light_position[] = {1.0f, 1.0f, 1.0f, 1.0f};
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
```

The 4th component (w) determines light type:
- **w = 1.0**: Positional light (point light at x, y, z)
- **w = 0.0**: Directional light (sun-like, direction from origin to x, y, z)

### Light Colors

```c
GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
```

### Spotlights

Create a focused beam of light:

```c
GLfloat spot_direction[] = {0.0f, -1.0f, 0.0f};
glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0f);  /* Cone angle (0-90) */
glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f);  /* Concentration (0-128) */
```

### Attenuation

Light intensity decreases with distance:

```c
glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);
glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
```

Attenuation = `1 / (constant + linear*d + quadratic*d²)`

## Materials

Materials define how surfaces respond to light.

### Material Colors

```c
GLfloat mat_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat mat_diffuse[] = {0.8f, 0.0f, 0.0f, 1.0f};  /* Red */
GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};  /* White highlights */
GLfloat mat_shininess[] = {50.0f};  /* 0-128, higher = shinier */

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
```

### Emissive Materials

Self-illuminating surfaces:

```c
GLfloat mat_emission[] = {0.3f, 0.3f, 0.0f, 1.0f};
glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
```

### Face Selection

Apply materials to:
- `GL_FRONT` - Front-facing polygons
- `GL_BACK` - Back-facing polygons
- `GL_FRONT_AND_BACK` - Both sides

## Normals

**Normals** are vectors perpendicular to surfaces. They're **essential** for lighting—without proper normals, lighting won't work correctly.

### Setting Normals

```c
glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.0f, 1.0f);  /* Normal pointing toward +Z */
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, 0.0f);
    glVertex3f( 0.0f,  1.0f, 0.0f);
glEnd();
```

Like colors, the normal remains active until you set a new one:

```c
glBegin(GL_QUADS);
    /* Front face */
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    
    /* Back face */
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
glEnd();
```

### Normal Normalization

Normals should be **unit vectors** (length 1). If you scale objects, normals get scaled too:

```c
glEnable(GL_NORMALIZE);  /* Automatically normalize normals (slower) */
/* OR */
glEnable(GL_RESCALE_NORMAL);  /* Faster, only for uniform scaling */
```

## Color Material Mode

Convenient shortcut to use `glColor*` for materials:

```c
glEnable(GL_COLOR_MATERIAL);
glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

/* Now glColor affects ambient and diffuse materials */
glColor3f(1.0f, 0.0f, 0.0f);  /* Red material */
draw_sphere();

glColor3f(0.0f, 1.0f, 0.0f);  /* Green material */
draw_cube();
```

Options for `glColorMaterial`:
- `GL_AMBIENT`
- `GL_DIFFUSE`
- `GL_AMBIENT_AND_DIFFUSE` (most common)
- `GL_SPECULAR`
- `GL_EMISSION`

## Global Ambient Light

Background light affecting all surfaces:

```c
GLfloat global_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
```

## Two-Sided Lighting

By default, lighting only affects front faces:

```c
glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
```

Now back faces are lit too (useful for planes, open objects).

## Local Viewer

More accurate specular highlights (slightly slower):

```c
glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
```

## Common Lighting Setups

### Single White Light

```c
void setup_basic_lighting(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    GLfloat light_pos[] = {5.0f, 5.0f, 5.0f, 1.0f};
    GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    glEnable(GL_NORMALIZE);
}
```

### Shiny Metal Material

```c
void set_gold_material(void) {
    GLfloat mat_ambient[] = {0.24725f, 0.1995f, 0.0745f, 1.0f};
    GLfloat mat_diffuse[] = {0.75164f, 0.60648f, 0.22648f, 1.0f};
    GLfloat mat_specular[] = {0.628281f, 0.555802f, 0.366065f, 1.0f};
    GLfloat mat_shininess = 51.2f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}
```

### Matte Plastic Material

```c
void set_plastic_material(void) {
    GLfloat mat_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat mat_diffuse[] = {0.55f, 0.0f, 0.0f, 1.0f};
    GLfloat mat_specular[] = {0.7f, 0.6f, 0.6f, 1.0f};
    GLfloat mat_shininess = 32.0f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}
```

## This Chapter's Example

Demonstrates:
1. Multiple light sources
2. Different material types
3. Directional vs positional lights
4. Spotlight effects
5. Material presets
6. Normal visualization

### Controls
- **1-5**: Switch material presets
- **L**: Toggle lights on/off
- **N**: Toggle normal visualization
- **Arrow keys**: Move light

## Common Issues

### Everything is Black

**Causes**:
1. Forgot to enable lighting: `glEnable(GL_LIGHTING);`
2. Forgot to enable at least one light: `glEnable(GL_LIGHT0);`
3. No normals or incorrect normals
4. Material colors are black

### Lighting Looks Wrong

**Causes**:
1. Normals not normalized: Enable `GL_NORMALIZE`
2. Normals pointing wrong direction: Check your cross products
3. Light position in wrong coordinate space
4. Forgot to set material properties

### Flat Shading Instead of Smooth

```c
glShadeModel(GL_SMOOTH);  /* Smooth shading (default) */
glShadeModel(GL_FLAT);    /* Flat shading */
```

## Performance Tips

1. Minimize material changes (expensive)
2. Use color material mode when possible
3. Disable lights you don't need
4. Use directional lights (faster than positional)
5. Consider disabling specular for distant objects

## Exercises

1. **Three-Point Lighting**: Key light, fill light, rim light
2. **Material Library**: Create presets for common materials
3. **Moving Lights**: Animate light positions
4. **Day/Night Cycle**: Transition between lighting setups
5. **Normal Debugger**: Draw lines showing normal vectors

## What We Learned

- Fixed-function lighting model (Phong)
- Light sources (positional, directional, spot)
- Material properties
- The critical importance of normals
- Color material mode
- Common lighting setups

## Next Steps

[Chapter 9](../chapter_09/README.md) covers textures—adding images to surfaces for realistic detail.

---

**Files in this chapter**:
- `main.c` - Lighting demonstrations
- `materials.c/h` - Material presets library
- `Makefile` / `CMakeLists.txt` - Build files

