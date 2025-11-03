# Chapter 12: Vertex Arrays

Vertex arrays provide better performance than immediate mode by batching vertex data.

## Enabling Vertex Arrays

```c
glEnableClientState(GL_VERTEX_ARRAY);
glEnableClientState(GL_COLOR_ARRAY);
glEnableClientState(GL_NORMAL_ARRAY);
glEnableClientState(GL_TEXTURE_COORD_ARRAY);
```

## Setting Pointers

```c
GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f
};

glVertexPointer(3, GL_FLOAT, 0, vertices);
```

## Drawing

```c
glDrawArrays(GL_TRIANGLES, 0, 3);
/* Or with indices: */
GLuint indices[] = {0, 1, 2, 2, 3, 0};
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
```

Much faster than glBegin/glEnd for large meshes!

---

[Chapter 13](../chapter_13/README.md)

