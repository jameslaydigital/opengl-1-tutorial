# Chapter 9: Textures in OpenGL 1.1

## Introduction

Textures add realistic detail to surfaces by mapping images onto geometry. This chapter covers texture loading, filtering, wrapping, and coordinates.

## Texture Basics

A **texture** is an image applied to a surface. Instead of using flat colors, you map pixels from the texture image onto your geometry.

## Texture Objects

Modern approach to managing textures:

```c
GLuint texture_id;
glGenTextures(1, &texture_id);  /* Generate texture name */
glBindTexture(GL_TEXTURE_2D, texture_id);  /* Make it active */

/* Now texture operations affect this texture */
```

To use multiple textures:

```c
GLuint textures[3];
glGenTextures(3, textures);

/* Bind first texture */
glBindTexture(GL_TEXTURE_2D, textures[0]);
/* Load and configure... */

/* Bind second texture */
glBindTexture(GL_TEXTURE_2D, textures[1]);
/* Load and configure... */
```

Delete textures when done:

```c
glDeleteTextures(1, &texture_id);
```

## Loading Texture Data

```c
glTexImage2D(GL_TEXTURE_2D,    /* Target */
             0,                 /* Mipmap level */
             GL_RGB,            /* Internal format */
             width,             /* Width */
             height,            /* Height */
             0,                 /* Border (must be 0) */
             GL_RGB,            /* Format of data */
             GL_UNSIGNED_BYTE,  /* Data type */
             pixels);           /* Pixel data */
```

Common formats:
- `GL_RGB` - 24-bit color
- `GL_RGBA` - 32-bit color with alpha
- `GL_LUMINANCE` - Grayscale
- `GL_LUMINANCE_ALPHA` - Grayscale + alpha

## Pixel Alignment

OpenGL assumes rows are aligned to 4-byte boundaries by default. For images with other alignments:

```c
glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  /* No alignment */
```

Common when loading RGB (3 bytes/pixel) images.

## Texture Parameters

### Filtering

Control how texture is sampled:

```c
/* Minification (texture smaller than surface) */
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

/* Magnification (texture larger than surface) */
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
```

Options:
- `GL_NEAREST` - Nearest neighbor (pixelated, fast)
- `GL_LINEAR` - Bilinear filtering (smooth, slower)
- `GL_LINEAR_MIPMAP_LINEAR` - Trilinear (mipmaps only)

### Wrapping

Control what happens outside 0-1 texture coordinates:

```c
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
```

Options:
- `GL_REPEAT` - Tile the texture
- `GL_CLAMP` - Clamp to edge
- `GL_CLAMP_TO_EDGE` - Better edge clamping (if available)

## Mipmaps

Mipmaps are pre-computed smaller versions of textures, improving quality and performance for distant objects.

### Generating Mipmaps (GLU)

```c
gluBuild2DMipmaps(GL_TEXTURE_2D,
                  GL_RGB,
                  width, height,
                  GL_RGB,
                  GL_UNSIGNED_BYTE,
                  pixels);
```

This automatically generates all mipmap levels. Much easier than `glTexImage2D` + manual mipmap creation.

Then use mipmap filtering:

```c
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                GL_LINEAR_MIPMAP_LINEAR);
```

## Texture Coordinates

Map texture image to geometry using coordinates (s, t) ranging from 0 to 1:

```c
glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  /* Bottom-left of texture */
    glVertex3f(-1.0f, -1.0f, 0.0f);
    
    glTexCoord2f(1.0f, 0.0f);  /* Bottom-right of texture */
    glVertex3f(1.0f, -1.0f, 0.0f);
    
    glTexCoord2f(1.0f, 1.0f);  /* Top-right of texture */
    glVertex3f(1.0f, 1.0f, 0.0f);
    
    glTexCoord2f(0.0f, 1.0f);  /* Top-left of texture */
    glVertex3f(-1.0f, 1.0f, 0.0f);
glEnd();
```

Like colors and normals, texture coordinates are per-vertex attributes.

## Enabling Texturing

```c
glEnable(GL_TEXTURE_2D);

/* Draw textured geometry */

glDisable(GL_TEXTURE_2D);
```

## Texture Modes

Control how textures combine with lighting/colors:

```c
glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode);
```

Modes:
- `GL_REPLACE` - Use texture color only
- `GL_MODULATE` - Multiply texture × material/color (default)
- `GL_DECAL` - Decal (blend based on alpha)
- `GL_BLEND` - Blend with constant color

## Loading Image Files

OpenGL doesn't provide image loading. You need a library or write your own.

### Option 1: stb_image (Recommended)

```c
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int width, height, channels;
unsigned char* data = stbi_load("texture.png", &width, &height, &channels, 0);

if (data) {
    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height,
                      format, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}
```

### Option 2: Simple TGA Loader

TGA is simple to parse (see example code).

### Option 3: PPM (Very Simple)

ASCII PPM files are trivial to load (good for learning).

## Texture Matrix

Transform texture coordinates:

```c
glMatrixMode(GL_TEXTURE);
glLoadIdentity();
glTranslatef(0.5f, 0.5f, 0.0f);
glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
glScalef(2.0f, 2.0f, 1.0f);
glMatrixMode(GL_MODELVIEW);  /* Switch back! */
```

Useful for:
- Scrolling textures (animation)
- Texture rotation
- Tiling control

## This Chapter's Example

Demonstrates:
1. Basic texture loading
2. Different filtering modes
3. Wrapping modes
4. Texture coordinates
5. Mipmaps
6. Texture animation

### Controls
- **1-3**: Switch filtering mode
- **W**: Change wrap mode
- **T**: Toggle texture animation

## Common Issues

### Texture Doesn't Appear

**Causes**:
1. Forgot `glEnable(GL_TEXTURE_2D)`
2. No texture bound
3. Texture coordinates not set
4. Lighting enabled with wrong mode (use `GL_MODULATE`)

### Texture Looks Wrong

**Causes**:
1. Wrong pixel format
2. Wrong alignment: `glPixelStorei(GL_UNPACK_ALIGNMENT, 1)`
3. Width/height swapped
4. Texture coordinates flipped

### Texture is Black

**Causes**:
1. Failed to load image
2. Texture parameters not set
3. Lighting making it dark (try `GL_REPLACE` mode)

### Texture is Blurry

**Cause**: Using `GL_LINEAR` magnification on small textures.

**Solution**: Use `GL_NEAREST` or higher resolution textures.

## Performance Tips

1. Use mipmaps for distant objects
2. Use power-of-2 dimensions (256x256, 512x512, etc.) for compatibility
3. Batch objects by texture to minimize texture switching
4. Use texture compression (extensions)
5. Use appropriate internal formats (RGB vs RGBA)

## Exercises

1. **Textured Cube**: Load 6 different textures, one per face
2. **Scrolling Texture**: Animate texture coordinates for flowing water effect
3. **Multitexture**: Combine two textures (requires extensions)
4. **Texture Atlas**: Pack multiple images into one texture
5. **Procedural Texture**: Generate checkerboard pattern in code

## What We Learned

- Texture objects and management
- Loading texture data with glTexImage2D
- Filtering and wrapping modes
- Mipmaps and gluBuild2DMipmaps
- Texture coordinates
- Common image loading strategies

## Next Steps

[Chapter 10](../chapter_10/README.md) covers commonly-used OpenGL state: blending, fog, and polygon modes.

---

**Files in this chapter**:
- `main.c` - Texture demonstrations
- `texture_loader.c/h` - Simple TGA loader
- `stb_image.h` - Single-header image library (optional)
- `Makefile` / `CMakeLists.txt` - Build files
- `textures/` - Sample textures

