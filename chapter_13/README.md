# Chapter 13: Input & Interaction with GLUT

## Keyboard Input

```c
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': case 'W': camera.z -= 0.1f; break;
        case 's': case 'S': camera.z += 0.1f; break;
        case 27: exit(0); /* ESC */
    }
}
glutKeyboardFunc(keyboard);
```

## Special Keys

```c
void special(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: /* ... */ break;
        case GLUT_KEY_F1: /* ... */ break;
    }
}
glutSpecialFunc(special);
```

## Mouse

```c
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        /* Handle left click */
    }
}
glutMouseFunc(mouse);
```

## Camera Controls

Implement orbit camera, FPS controls, etc. See example code.

---

[Chapter 14](../chapter_14/README.md)

