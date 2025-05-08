#include "matrix.h"
#include <stdio.h>
#include <math.h>

void init_zero_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}

void print_matrix(const float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void init_identity_matrix(float matrix[3][3]) {
    init_zero_matrix(matrix);
    matrix[0][0] = 1;
    matrix[1][1] = 1;
    matrix[2][2] = 1;
}

void multiply_matrix_by_scalar(const float matrix[3][3], const float scalar, float result[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result[i][j] = matrix[i][j] * scalar;
        }
    }
}

void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3]) {
    init_zero_matrix(c);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void transform_point(const float matrix[3][3], float point[3]) {
    float temp[3];
    for (int i = 0; i < 3; ++i) {
        temp[i] = 0.0f;
        for (int j = 0; j < 3; ++j) {
            temp[i] += matrix[i][j] * point[j];
        }
    }
    for (int i = 0; i < 3; i++)
    {
        point[i] = temp[i];
    }
    
}


void scale(float matrix[3][3], float sx, float sy) {
    float scale_matrix[3][3] = {
        {sx, 0.0f, 0.0},
        {0.0f, sy, 0.0},
        {0.0f, 0.0f, 1.0f}
    };
    float result[3][3];
    multiply_matrices(scale_matrix, matrix, result);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = result[i][j];
        }
    }
}

void shift(float matrix[3][3], float tx, float ty) {
    float shift_matrix[3][3] = {
        {1.0f, 0.0f, tx},
        {0.0f, 1.0f, ty},
        {0.0f, 0.0f, 1.0f}
    };

    float result[3][3];
    multiply_matrices(shift_matrix, matrix, result);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = result[i][j];
        }
    }
}

void rotate(float matrix[3][3], float angle) {
    float radians = angle * (3.14159265 / 180.0f);
    float cos_angle = cosf(radians);
    float sin_angle = sinf(radians);

    float rotate_matrix[3][3] = {
        {cos_angle, -sin_angle, 0.0f},
        {sin_angle, cos_angle, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    float result[3][3];
    multiply_matrices(rotate_matrix, matrix, result);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = result[i][j];
        }
    }
}