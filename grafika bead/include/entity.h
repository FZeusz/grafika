#ifndef ENTITY_H
#define ENTITY_H

#include "utils.h"
#include "texture.h"
#include <obj/model.h>

typedef struct Entity
{
    Model model;
    Material material;
    GLuint texture_id;
    vec3 pos;
    vec3 rot;
    vec3 scale;
} Entity;

void init_Targy(Entity* Entity, char* obj, char* texture);

#endif /* ENTITY_H */