# Chapter 11: Display Lists

Display lists precompile geometry for faster rendering.

## Creating Display Lists

```c
GLuint list_id = glGenLists(1);
glNewList(list_id, GL_COMPILE);
    /* Draw geometry */
    draw_complex_model();
glEndList();

/* Later, call it: */
glCallList(list_id);
```

## When to Use

- Static geometry that doesn't change
- Complex models rendered multiple times
- Performance-critical sections

## Limitations

- Can't modify geometry once compiled
- Some state changes don't work inside lists
- Deprecated in modern OpenGL

---

[Chapter 12](../chapter_12/README.md)

