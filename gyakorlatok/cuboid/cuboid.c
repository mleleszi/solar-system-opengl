#include "cuboid.h"
#include <math.h>

void set_size(Cuboid* cuboid, double x, double y, double z){
  if(x > 0.0) cuboid->x = x;
  else cuboid->x = NAN;

  if(y > 0.0) cuboid->y = y;
  else cuboid->y = NAN;

  if(z >0.0) cuboid->z = z;
  else cuboid->z = NAN;
}

double calc_volume(Cuboid* cuboid){
  return (cuboid->x) * (cuboid->y) * (cuboid->z);
}

double calc_surface(Cuboid* cuboid){
  return 2 * (cuboid->x) * (cuboid->y) + 2 * (cuboid->x) * (cuboid->z) + 2 * (cuboid->y) * (cuboid->z);
}
int has_square(Cuboid* cuboid){
  if(isnan(cuboid->x) || isnan(cuboid->y) || isnan(cuboid->z)) return 0;
  if((cuboid->x) == (cuboid->y) || (cuboid->x) == (cuboid->z) || (cuboid->y) == (cuboid->z)) return 1;
  return 0;
}
