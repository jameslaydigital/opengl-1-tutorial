# Chapter 19: Packaging a Demo

## Static vs Dynamic Linking

### Dynamic (Recommended)
- Smaller executables
- System provides libraries
- User needs FreeGLUT installed

### Static
- Larger executables
- Self-contained
- No dependencies

## Asset Paths

```c
/* Wrong: assumes working directory */
FILE* f = fopen("texture.tga", "rb");

/* Better: relative to executable */
#ifdef _WIN32
    /* Use GetModuleFileName */
#else
    /* Use readlink on /proc/self/exe or argv[0] */
#endif
```

## Distribution

### Linux
```bash
# Package with assets
my_demo
├── demo (executable)
├── textures/
└── models/
```

### Windows
- Include FreeGLUT DLL
- Visual C++ redistributables if needed

### macOS
- Create .app bundle
- Include frameworks

---

[Chapter 20](../chapter_20/README.md)

