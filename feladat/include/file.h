#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include "file.h"
#include "scene.h"


// read planet data from file
void readFromFile(Planet* planets, FILE* fp);

#endif
