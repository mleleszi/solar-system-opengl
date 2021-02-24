#include "matrix.h"
#include <stdio.h>
#include <math.h>

int main(){

  float a[3][3] = {
    {1.0f, 10.0f, 5.0f},
    {0.0f, 1.0f, 5.0f},
    {0.0f, 0.0f, 1.0f}
  };

  float b[3][3];
  float c[3][3];
  float m[3][3];
  float p[] = {1.0 , 2.0, 1.0};


  init_zero_matrix(b);
  b[1][1] = 8.0f;
  b[2][0] = -3.0f;
  b[2][2] = 5.0f;

  printf("\n");
  init_identitiy_matrix(a);
  print_matrix(a);
  printf("\n");

  mult_by_scalar(b, 2, a);
  print_matrix(b);
  printf("\n");

  print_vector(p);
  printf("\n");


  init_translation_matrix(m, 10, 10);
  transform_point(p, m);
  print_vector(p);
  printf("\n");

  init_rotation_matrix(m, M_PI);
  transform_point(p, m);
  print_vector(p);
  printf("\n");

  init_scale_matrix(m, 2, 2);
  transform_point(p, m);
  print_vector(p);
  printf("\n");


  return 0;
}
