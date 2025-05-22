#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "entity.h"
#include <obj/model.h>


typedef struct Scene
{
    Entity *cube; 
    Entity car;
    int cube_length;
    Material material;
    int cube_rows;
    int cube_columns;
    bool enableCar;
    GLuint get_inTexture;
    bool get_in;
    Entity *ali;
    int one;
    GLuint getAliTexture;
    bool isAli;
    int aliLength;
    GLuint menuTexture;
    bool isMenuActive;
    GLuint overTexture;
    bool fog;
} Scene;


/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene);
/**
 * Render the scene objects.
 */
void render_scene(Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void render_obj();

void destrox_scene();

void render_menu_texture(GLuint texture);

#endif /* SCENE_H */
