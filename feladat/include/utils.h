#ifndef UTILS_H
#define UTILS_H


// GLSL-like three dimensional vector
typedef struct vec3{
    float x;
    float y;
    float z;
} vec3;

// converts degrees to radians
double degree_to_radian(double degree);

// color
typedef struct Color{
    float red;
    float green;
    float blue;
} Color;

// material
typedef struct Material{
    struct Color ambient;
    struct Color diffuse;
    struct Color specular;
    float shininess;
} Material;

#endif
