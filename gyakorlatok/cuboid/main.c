#include "cuboid.h"
#include <stdio.h>

int main(){
  Cuboid cuboid;
  double volume;
  double surface;
  int hasSquare;

  set_size(&cuboid, 10, 10, 10);
  volume = calc_volume(&cuboid);
  surface = calc_surface(&cuboid);
  hasSquare = has_square(&cuboid);

  printf("Cuboid volume: %lf\nCuboid surface: %lf\nHas a square side: ", volume, surface);
  printf(hasSquare ? "true" : "false");

  return 0;
}
