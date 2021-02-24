#ifndef CUBOID_H
#define CUBOID_H

typedef struct Cuboid{
  double x;
  double y;
  double z;
} Cuboid;

void set_size(Cuboid* cuboid, double x, double y, double z);
double calc_volume(Cuboid* cuboid);
double calc_surface(Cuboid* cuboid);
int has_square(Cuboid* cuboid);

#endif
