#include "entity.h"

#include <obj/model.h>
#include <obj/load.h>
#include <obj/draw.h>

void init_Entity(Entity* entity, char* obj, char* texture){
    load_model(&(entity->model), obj);
    entity->texture_id = load_texture(texture);


    entity->pos.x=0;
    entity->pos.y=0;
    entity->pos.z=0;

    entity->rot.x=0;
    entity->rot.y=0;
    entity->rot.z=0;

    entity->scale.x=1;
    entity->scale.y=1;
    entity->scale.z=1;

}