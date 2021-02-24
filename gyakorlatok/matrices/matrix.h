#ifndef MATRIX_H
#define MATRIX_H


// Initializes all elemnts of a matrix to zero
void init_zero_matrix(float matrix[3][3]);

// Initializes an identity matrix
void init_identitiy_matrix(float matrix[3][3]);

// Prints the elements of a matrix
void print_matrix(float matrix[3][3]);

// Prints a vector
void print_vector(float v[3]);

// Add matrices
void add_matrices(float a[3][3], float b[3][3], float c[3][3]);

// Multiply by scalar.
void mult_by_scalar(float result[3][3], float scalar, float matrix[3][3]);

// Multiplies a matrix by a matrix
void multiply_matrices(float a[3][3], float b[3][3], float c[3][3]);

// Transforms a point by a  matrix
void transform_point(float p[3], float m[3][3]);

// Initializes a scale matrix
void init_scale_matrix(float m[3][3], float sx, float sy);

// Initializes a rotation matrix
void init_rotation_matrix(float m[3][3], float alpha);

// Initializes a translation matrix
void init_translation_matrix(float m[3][3], float dx, float dy);

#endif
