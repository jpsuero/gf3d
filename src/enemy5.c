#include "simple_logger.h"
#include "gfc_types.h"
#include "enemy5.h"
#include "iceshard.h"

void enemy5_think(Entity *self);
void enemy5_update(Entity *self);


Entity *enemy5_new(Vector3D position, int tag)
{
    Entity *ent = NULL;
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no enemy5 for you!");
        return NULL;
    }
    
    ent->model = gf3d_model_load("cube3");
    ent->think = enemy5_think;
    ent->update = enemy5_update;
    vector3d_copy(ent->position,position);
    //vector3d_copy(ent->velocity,direction);
    ent->scale = vector3d(5,5,5);
    ent->shootBuffer = 0;
    ent->health = 3;
    ent->tag = tag;
    return ent;
}


void enemy5_think(Entity *self)
{
    //self->rotation.x += .0050;
    //self->rotation.y += .0050;
    //self->rotation.z += .0050;

    self->circle = gfc_sphere(self->position.x, self->position.y,self->position.z, 5);

    Vector2D direction;
    Vector3D target = getPlayer()->position;
    direction.x = target.x - self->position.x;
    direction.y = target.y - self->position.y;
    vector2d_set_magnitude(&direction,.4);

    if(getPlayer()->level != 4)entity_free(self);

    self->shootBuffer++;
    if(self->shootBuffer == 10 && self->isFrozen == 0)
    {
        iceshard(self->position, vector3d(direction.x, direction.y, 0), 2);
    }
    if(self->shootBuffer > 5000)self->shootBuffer =0;

}

void enemy5_update(Entity *self)
{        
    
}

/*eol@eof*/
