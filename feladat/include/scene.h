#ifndef SCENE_H
#define SCENE_H

#include <obj/model.h>
#include "camera.h"
#include "texture.h"

typedef struct Planet{
    float radius;
    float distance;
    float orbit_speed;
    float orbit;
    float rotation_speed;
    float rotation;
    float axis_tilt;
} Planet;

typedef struct Scene{
    Model geoid;
    Material material;
    Color ambient;
    GLuint sun_texture_id;
    GLuint mercury_texture_id;
    GLuint venus_texture_id;
    GLuint earth_texture_id;
    GLuint mars_texture_id;
    GLuint jupiter_texture_id;
    GLuint saturn_texture_id;
    GLuint uranus_texture_id;
    GLuint neptune_texture_id;
    GLuint moon_texture_id;
    GLuint skybox_texture_id;

    int drawOrbit;
    int animate;
} Scene;

// init scene by loading models
void init_scene(Scene* scene);

// set the lighting of the scene
void set_lighting(Scene* scene);

// set the current material
void set_material(const Material* material);

// draw the sccene objects
//void draw_scene(Scene* scene);

// call to draw the planets
void draw_planets(Scene* scene);

// call to draw orbit trail of a planet
void draw_orbit_trail(float radius);

#endif
