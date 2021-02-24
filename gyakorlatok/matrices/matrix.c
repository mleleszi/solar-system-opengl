#include "matrix.h"
#include <stdio.h>
#include <math.h>


void init_zero_matrix(float matrix[3][3]){

  int i, j;
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      matrix[i][j] = 0.0f;
    }
  }
}

void init_identitiy_matrix(float matrix[3][3]){

    int i, j;
    for(i = 0; i < 3; i++){
      for(j = 0; j < 3; j++){
        if(i == j) matrix[i][j] = 1.0f;
        else matrix[i][j] = 0.0f;
      }
    }
}

void print_matrix(float matrix[3][3]){

  int i, j;
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      printf("%4.4f ", matrix[i][j]);
    }
    printf("\n");
  }
}

void print_vector(float v[3]){

  int i;
  for(i = 0; i < 3; i++){
    printf("%.4f ", v[i]);
  }
}

void add_matrices(float a[3][3], float b[3][3], float c[3][3]){

  int i, j;
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      c[i][j] = a[i][j] + b[i][j];
    }
  }
}

void mult_by_scalar(float result[3][3], float scalar, float matrix[3][3]){

  int i, j;
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      result[i][j] = matrix[i][j] * scalar;
    }
  }
}

void multiply_matrices(float a[3][3], float b[3][3], float c[3][3]){

  init_zero_matrix(c);
  int i, j, k;
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      for(k = 0; k < 3; k++){
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

void transform_point(float p[3], float m[3][3]){

  int i, j;
  float result[3] = {0.0, 0.0, 0.0};

  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      result[i] += m[i][j] * p[j];
    }
  }

  for(i = 0; i < 3; i++){
    p[i] = result[i];
  }
}

void init_scale_matrix(float m[3][3], float sx, float sy){

  init_identitiy_matrix(m);
  m[0][0] = sx;
  m[1][1] = sy;
}

void init_rotation_matrix(float m[3][3], float alpha){

  init_identitiy_matrix(m);
  m[0][0] = cos(alpha);
  m[0][1] = -sin(alpha);
  m[1][0] = sin(alpha);
  m[1][1] = cos(alpha);
}

void init_translation_matrix(float m[3][3], float dx, float dy){

  init_identitiy_matrix(m);
  m[0][2] = dx;
  m[1][2] = dy;

}
