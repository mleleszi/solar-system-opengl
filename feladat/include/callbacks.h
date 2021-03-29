#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <GL/glut.h>
#include "camera.h"
#include "scene.h"


int w, h;
int frame;
long time, timebase;
char s[50];

// camera
Camera camera;

// scene
Scene scene;

// called when graphical content needs to be displayed
void display();

// called after window resizing
void reshape(GLsizei width, GLsizei height);

// called after pressing mouse button
void mouse(int button, int state, int x, int y);

// called when moving mouse
void motion(int x, int y);

// called after pressing a key
void keyboard(unsigned char key, int x, int y);

// called after releasing a key
void keyboard_up(unsigned char key, int x, int y);

// called after pressing a special key
void specialFunc(int key, int x, int y);

// calculates frames per second
void calc_fps();

// called when there is no other event
void idle();

#endif
