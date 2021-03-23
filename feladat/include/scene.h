#ifndef SCENE_H
#define SCENE_H

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

} Scene;

// init scene by loading models
void init_scene(Scene* scene);

// draw the sccene objects
void draw_scene(Scene* scene);

// call to draw a planet
void draw_planet(Planet* planet);

// call to draw orbit trail of a planet
void draw_orbit_trail(Planet* planet);

#endif
