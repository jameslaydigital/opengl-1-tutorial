# Chapter 18: Cross-Platform Notes

## Windows (WGL)

GLUT hides most WGL complexity. For raw WGL:
- Create device context
- Choose pixel format
- Create rendering context
- Make it current

## Linux (GLX)

GLUT abstracts GLX. Modern Linux uses Mesa drivers (excellent OpenGL support).

## macOS

**Important**: OpenGL deprecated since macOS 10.14
- Still works but warnings appear
- Maximum: OpenGL 4.1
- Apple recommends Metal instead
- Suppress warnings: `-Wno-deprecated-declarations`

## Best Practices

1. Use GLUT/GLFW/SDL for portability
2. Test on multiple platforms
3. Handle different GL versions gracefully
4. Query extensions before using

---

[Chapter 19](../chapter_19/README.md)

