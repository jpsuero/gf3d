#include "simple_logger.h"
#include "gfc_types.h"
#include "enemy3.h"

void enemy3_think(Entity *self);
void enemy3_update(Entity *self);


Entity *enemy3_new(Vector3D position, int tag)
{
    Entity *ent = NULL;
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no enemy3 for you!");
        return NULL;
    }
    
    ent->model = gf3d_model_load("cube4");
    ent->think = enemy3_think;
    ent->update = enemy3_update;
    vector3d_copy(ent->position,position);
    //vector3d_copy(ent->velocity,direction);
    ent->scale = vector3d(10,10,10);
    ent->isFrozen = 0;
    ent->tag = tag;
    return ent;
}


void enemy3_think(Entity *self)
{
    if(!self)return;

    if(getPlayer()->level != 3)entity_free(self);

    if(self->isFrozen == 0)
    {
        if(self->position.z >= 150)
        {
            self->down = 1;
        }

        if(self->position.z <= 0)
        {
            self->down = 0;
        }

        if(self->down == 1)
        {
            self->position.z -= .5;
        }
        else
        {
            self->position.z +=.1;
        }
    }


    self->circle = gfc_sphere(self->position.x, self->position.y,self->position.z, 10);


    if(gfc_point_in_sphere(getPlayer()->position, self->circle))
    {
        getPlayer()->scale.z = .5;
        getPlayer()->health--;
        entity_free(self);
        return;
    }


}

void enemy3_update(Entity *self)
{        
    
}

/*eol@eof*/
