#include "matrix.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	float a[3][3] = {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  1.0f},
        {-2.0f,  1.0f, -4.0f}
    };
	float b[3][3] = {
        {2.0f, -1.0f,  4.0f},
        {0.0f,  3.0f, -2.0f},
        {1.0f, -5.0f,  3.0f}
    };
	float c[3][3];
    float p1[3] = {2.0f, -1.0f, 3.0f};


    printf("A matrix\n");
    print_matrix(a);
    printf("\nB matrix\n");
    print_matrix(b);

    printf("\nA + B\n");
    add_matrices(a, b, c);
    print_matrix(c);

    printf("\nA * 2.3\n");
    multiply_matrix_by_scalar(a, 2.3, c);
    print_matrix(c);
    
    printf("\nA * B\n");
    multiply_matrices(a, b, c);
    print_matrix(c);

    printf("\nB * p1(2, -1, 3)\n");
    transform_point(b, p1);
    printf("%f\n%f\n%f\n", p1[0], p1[1], p1[2]);

    printf("\nScale, A * (2, -3, 1)\n");
    scale(a, 2, -3);
    print_matrix(a);

    printf("\nShift, B * (3, 4, 1)\n");
    shift(b, 3, 4);
    print_matrix(b);

    printf("\nRotate, A * 45deg\n");
    rotate(a, 45);
    print_matrix(a);

	return 0;
}

