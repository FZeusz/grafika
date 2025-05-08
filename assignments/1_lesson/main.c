#include <stdio.h>
#include <stdbool.h>

struct Cuboid {
    float lenght;
    float width;
    float height;
} ; 

//Assigns the values ​​to the cube
void set_size(struct Cuboid *cube, float lenght, float width, float height) {
    if (lenght > 0 && width > 0 && height > 0) {
        cube->lenght = lenght;
        cube->width = width;
        cube->height = height;
    }
    else {
        printf("Error: All dimensions must be positive numbers.\n");
    }
}

//Calculates the volume of the cube
float calc_volume(struct Cuboid *cube) {
    return cube->height * cube->lenght * cube->width;
}

//Calculates the surface of the cube
float calc_surface(struct Cuboid *cube) {
    return 2 * (cube->height * cube->lenght + cube->height * cube->width + cube->lenght * cube->width);
}

//Examine the rectangle to see if it has a square face
bool is_square(struct Cuboid *cube) {
    if (cube->height == cube->lenght || cube->lenght == cube->width || cube->height == cube->width)
    {
        return true;
    }
    return false;
}

int main() {
    struct Cuboid cube;
    set_size(&cube, 2, 2, 6.1);

    printf("Volume: %g\n", calc_volume(&cube));

    printf("Surface: %g\n", calc_surface(&cube));

    printf(is_square(&cube) ? "Does have a square face" : "Does NOT have a square face");
    return 0;
}