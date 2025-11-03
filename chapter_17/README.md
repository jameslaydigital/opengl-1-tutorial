# Chapter 17: Debugging & Introspection

## Check OpenGL Errors

```c
void check_gl_error(const char* context) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        fprintf(stderr, "GL Error in %s: 0x%x\n", context, err);
    }
}
```

Call after suspicious operations.

## Query Capabilities

```c
printf("Vendor: %s\n", glGetString(GL_VENDOR));
printf("Renderer: %s\n", glGetString(GL_RENDERER));
printf("Version: %s\n", glGetString(GL_VERSION));

GLint max_texture_size;
glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_texture_size);
printf("Max texture size: %d\n", max_texture_size);
```

## Visual Debugging

- Draw normals as lines
- Use wireframe mode: `glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);`
- Draw bounding boxes
- Color-code different object types

---

[Chapter 18](../chapter_18/README.md)

