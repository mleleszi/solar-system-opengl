#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Model cube;
    Material material;
    GLuint texture_id;
    GLuint texture_id1;
    GLuint texture_id2;
    GLuint texture_id3;
    GLuint texture_id4;
    GLuint texture_id5;
    GLuint texture_id6;

    float rotation;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

void update_scene(Scene* scene, double time);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

#endif /* SCENE_H */
