# Chapter 14: Text & UI Bits

## GLUT Bitmap Fonts

```c
void draw_text(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}
```

Available fonts: `GLUT_BITMAP_8_BY_13`, `GLUT_BITMAP_9_BY_15`, 
`GLUT_BITMAP_TIMES_ROMAN_10`, `GLUT_BITMAP_HELVETICA_18`, etc.

## Stroke Fonts

```c
glutStrokeCharacter(GLUT_STROKE_ROMAN, 'A');
```

Vector fonts that can be transformed.

## 2D Overlay

```c
/* Save 3D state */
glMatrixMode(GL_PROJECTION);
glPushMatrix();
glLoadIdentity();
gluOrtho2D(0, width, 0, height);
glMatrixMode(GL_MODELVIEW);
glPushMatrix();
glLoadIdentity();

/* Draw 2D UI */
draw_hud();

/* Restore 3D state */
glMatrixMode(GL_PROJECTION);
glPopMatrix();
glMatrixMode(GL_MODELVIEW);
glPopMatrix();
```

---

[Chapter 15](../chapter_15/README.md)

