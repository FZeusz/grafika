#ifndef MATRIX_H
#define MATRIX_H

/**
 * Initializes all elements of the matrix to zero.
 */
void init_zero_matrix(float matrix[3][3]);

/**
 * Print the elements of the matrix.
 */
void print_matrix(const float matrix[3][3]);

/**
 * Add matrices.
 */
void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

/**
 * Initialize the identity matrix
 */
void init_identity_matrix(float matrix[3][3]);

/**
 * Multiplies a matrix by a scalar
 * The input and output matrix can be the same
 */
void multiply_matrix_by_scalar(const float matrix[3][3], const float scalar, float result[3][3]);

/**
 * Multiply matrices
 */
void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

/**
 * Transforms a point using the given transformation matrix
 */
void transform_point(const float matrix[3][3], float point[3]);

/**
 * Scale transformation - modifies the transformation matrix to include scaling
 */
void scale(float matrix[3][3], float sx, float sy);

/**
 * Shift transformation - modifies the transformation matrix to include translation
 */
void shift(float matrix[3][3], float tx, float ty);

/**
 * Rotate transformation - modifies the transformation matrix to include rotation.
 * The angle is in DEGREES and rotation is around the origin.
 */
void rotate(float matrix[3][3], float angle);

#endif // MATRIX_H