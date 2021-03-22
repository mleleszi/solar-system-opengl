#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

typedef struct Camera{
    vec3 position;
    vec3 rotation;
    vec3 speed;
} Camera;

// initialize the camera to the start positon
void init_camera(Camera* camera);

// update the positon of the camera
void update_camera(Camera* camera, double time);

// apply the camera settings to the view transformation
void set_view(const Camera* camera);

// set the horinotal and vertical rotation of the view angle
void rotate_camera(Camera* camera, double horizontal, double vertical);

// set the horizontal speed of the camera
void set_camera_speed(Camera* camera, double speed);

// set the speed of left and righ steps
void set_camera_side_speed(Camera* camera, double speed);

// set the vertical speed of the camera
void set_camera_vertical_speed(Camera* camera, double speed);

#endif
