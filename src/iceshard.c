#include "simple_logger.h"
#include "gfc_types.h"
#include "entity.h"

//#include "gf3d_camera.h"
#include "iceshard.h"

void iceshard_think(Entity *self);
void iceshard_update(Entity *self);


Entity *iceshard(Vector3D position,  Vector3D direction)
{
    Entity *ent = NULL;
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no iceshard for you!");
        return NULL;
    }
    
    ent->model = gf3d_model_load("dino");
    ent->think = iceshard_think;
    ent->update = iceshard_update;
    vector3d_copy(ent->position,position);
    vector3d_copy(ent->velocity,direction);
    ent->scale = vector3d(.5,.5,.5);
    //ent->bounds = gfc_box(1,1,1,3,3,3);
    ent->tag = 6;
    return ent;
}


void iceshard_think(Entity *self)
{
    self->lifespan++;
    self->rotation.x += .0050;
    self->rotation.y += .0050;
    self->rotation.z += .0050;

    if(!self)return;
    
    
    /*Entity *col = collisionCheck(self);
    if(col->tag == 2)
    {
        col--;
        entity_free(self);
    }*/

    if(self->lifespan > 10000)
    {
        entity_free(self);
    }
    //vector3d_add(self->position,self->position, self->velocity);
}

void iceshard_update(Entity *self)
{        
    
}

/*eol@eof*/
