/*
 * materials.h - Material presets library
 */

#ifndef MATERIALS_H
#define MATERIALS_H

void material_apply(int preset);
const char* material_get_name(int preset);

/* Material preset indices */
#define MAT_EMERALD   0
#define MAT_JADE      1
#define MAT_RUBY      2
#define MAT_GOLD      3
#define MAT_SILVER    4
#define MAT_CHROME    5
#define MAT_PLASTIC   6
#define MAT_RUBBER    7

#endif /* MATERIALS_H */

