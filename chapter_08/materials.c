/*
 * materials.c - Material presets (based on SGI material library)
 */

#include <GL/glut.h>
#include "materials.h"

typedef struct {
    const char* name;
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float shininess;
} material_t;

static const material_t materials[] = {
    /* Emerald */
    {
        "Emerald",
        {0.0215f, 0.1745f, 0.0215f, 1.0f},
        {0.07568f, 0.61424f, 0.07568f, 1.0f},
        {0.633f, 0.727811f, 0.633f, 1.0f},
        76.8f
    },
    /* Jade */
    {
        "Jade",
        {0.135f, 0.2225f, 0.1575f, 1.0f},
        {0.54f, 0.89f, 0.63f, 1.0f},
        {0.316228f, 0.316228f, 0.316228f, 1.0f},
        12.8f
    },
    /* Ruby */
    {
        "Ruby",
        {0.1745f, 0.01175f, 0.01175f, 1.0f},
        {0.61424f, 0.04136f, 0.04136f, 1.0f},
        {0.727811f, 0.626959f, 0.626959f, 1.0f},
        76.8f
    },
    /* Gold */
    {
        "Gold",
        {0.24725f, 0.1995f, 0.0745f, 1.0f},
        {0.75164f, 0.60648f, 0.22648f, 1.0f},
        {0.628281f, 0.555802f, 0.366065f, 1.0f},
        51.2f
    },
    /* Silver */
    {
        "Silver",
        {0.19225f, 0.19225f, 0.19225f, 1.0f},
        {0.50754f, 0.50754f, 0.50754f, 1.0f},
        {0.508273f, 0.508273f, 0.508273f, 1.0f},
        51.2f
    },
    /* Chrome */
    {
        "Chrome",
        {0.25f, 0.25f, 0.25f, 1.0f},
        {0.4f, 0.4f, 0.4f, 1.0f},
        {0.774597f, 0.774597f, 0.774597f, 1.0f},
        76.8f
    },
    /* Red Plastic */
    {
        "Red Plastic",
        {0.0f, 0.0f, 0.0f, 1.0f},
        {0.5f, 0.0f, 0.0f, 1.0f},
        {0.7f, 0.6f, 0.6f, 1.0f},
        32.0f
    },
    /* Black Rubber */
    {
        "Black Rubber",
        {0.02f, 0.02f, 0.02f, 1.0f},
        {0.01f, 0.01f, 0.01f, 1.0f},
        {0.4f, 0.4f, 0.4f, 1.0f},
        10.0f
    }
};

const int num_materials = sizeof(materials) / sizeof(materials[0]);

void material_apply(int preset) {
    if (preset < 0 || preset >= num_materials) {
        preset = 0;
    }
    
    const material_t* mat = &materials[preset];
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat->specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat->shininess);
}

const char* material_get_name(int preset) {
    if (preset < 0 || preset >= num_materials) {
        return "Unknown";
    }
    return materials[preset].name;
}

