# Chapter 10: State You'll Use a Lot

## Blending and Transparency

Enable alpha blending:
```c
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
```

Draw transparent objects back-to-front for correct blending.

## Fog

Classic OpenGL fog:
```c
glEnable(GL_FOG);
glFogi(GL_FOG_MODE, GL_LINEAR);  /* or GL_EXP, GL_EXP2 */
GLfloat fog_color[] = {0.5f, 0.5f, 0.5f, 1.0f};
glFogfv(GL_FOG_COLOR, fog_color);
glFogf(GL_FOG_START, 5.0f);
glFogf(GL_FOG_END, 20.0f);
```

## Polygon Mode

```c
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  /* Wireframe */
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  /* Solid */
glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); /* Points */
```

## Line/Point Sizes

```c
glLineWidth(3.0f);
glPointSize(10.0f);
```

---

[Chapter 11](../chapter_11/README.md)

