# Chapter 15: Common Pitfalls

## "Why is everything black?"

1. **Lighting enabled but no lights**: `glEnable(GL_LIGHT0);`
2. **Missing normals**: Set `glNormal3f()` for each face
3. **Normals not normalized**: `glEnable(GL_NORMALIZE);`
4. **Wrong material settings**: Check ambient/diffuse values

## Z-Fighting

Two surfaces at same depth flicker. Solutions:
- Separate surfaces slightly
- Use better near/far plane ratio
- `glPolygonOffset()` for coplanar polygons

## Texture Problems

- **Black texture**: Check if file loaded, `glEnable(GL_TEXTURE_2D)`
- **Blurry**: Wrong filter mode or missing mipmaps
- **Wrong alignment**: `glPixelStorei(GL_UNPACK_ALIGNMENT, 1);`

---

[Chapter 16](../chapter_16/README.md)

