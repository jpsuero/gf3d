#include "platform.h"
#include "simple_json.h"
#include "simple_logger.h"
#include "gfc_primitives.h"
#include "gfc_types.h"
#include "entity.h"

void platform_think(Entity *self);
void platform_update(Entity *self);


Entity *platform_new(Vector3D position, int type, int level)
{
    Entity *ent = NULL;
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no platform for you!");
        return NULL;
    }
    vector3d_copy(ent->position,position);
    ent->model = gf3d_model_load("cube2");
    ent->think = platform_think;
    ent->update = platform_update;
    ent->scale = vector3d(10,10,5);
    ent->platformType = type;
    ent->level = level;
    ent->tag = 3;
    return ent;
}


void platform_think(Entity *self)
{
    Entity * player = getPlayer();
    Vector3D position;
    if(!self)return;
    if(!player)return;

    if(self->level != player->level)
    {
        entity_free(self);
    }

    vector3d_copy(position,self->position);
    
    if(self->platformType == 0)
    {
        self->scale = vector3d(100,100,1);
        self->bounds = gfc_box(position.x-100, self->position.y-100, position.z,200,200,1);
    }
    else
    {
        self->bounds = gfc_box(position.x-5, self->position.y-5, position.z,10,10,5);
    }
    
    //side to side movement
    if(self->platformType == 2)
    {
        self->buffer++;
        if(self->buffer <= 300)
        {
            self->position.x +=.1;
            if(gfc_box_overlap(self->bounds, player->bounds))
            {
                player->position.x += .1;
            }
        }
        else if(self->buffer>=300 && self->buffer < 900)
        {
            self->position.x -= .1;
            if(gfc_box_overlap(self->bounds, player->bounds))
            {
                player->position.x -= .1;
            }
        }
        else 
        {
            self->buffer =-300;
        }
    }

}

void platform_update(Entity *self)
{        
    
}

/*eol@eof*/
