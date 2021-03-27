#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glut.h>

typedef GLubyte Pixel[3];

// load texture from file
GLuint load_texture(char* filename);

#endif
