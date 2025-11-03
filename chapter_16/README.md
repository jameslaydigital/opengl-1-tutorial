# Chapter 16: Performance Tips for OpenGL 1.1

## Minimize State Changes

State changes are expensive. Group drawing by:
1. Texture
2. Material
3. Blending mode

## Prefer Vertex Arrays

Much faster than `glBegin/glEnd`:
```c
glVertexPointer(3, GL_FLOAT, 0, vertices);
glDrawArrays(GL_TRIANGLES, 0, vertex_count);
```

## Use Display Lists

For static geometry:
```c
list_id = glGenLists(1);
glNewList(list_id, GL_COMPILE);
    /* Draw geometry */
glEndList();
/* Later: */
glCallList(list_id);
```

## Culling and Depth Test

Always enable for 3D:
```c
glEnable(GL_CULL_FACE);
glEnable(GL_DEPTH_TEST);
```

---

[Chapter 17](../chapter_17/README.md)

