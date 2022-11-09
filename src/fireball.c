#include "simple_logger.h"
#include "gfc_types.h"

//#include "gf3d_camera.h"
#include "fireball.h"

void fireball_think(Entity *self);
void fireball_update(Entity *self);


Entity *fireball(Vector3D position,  Vector3D direction)
{
    Entity *ent = NULL;
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no fireball for you!");
        return NULL;
    }
    
    ent->model = gf3d_model_load("dino2");
    ent->think = fireball_think;
    ent->update = fireball_update;
    vector3d_copy(ent->position,position);
    vector3d_copy(ent->velocity,direction);
    ent->scale = vector3d(.5,.5,.5);
    ent->tag = 6;
    return ent;
}


void fireball_think(Entity *self)
{
    self->lifespan++;
    self->rotation.x += .0050;
    self->rotation.y += .0050;
    self->rotation.z += .0050;

    if(self->lifespan > 10000)
    {
        entity_free(self);
    }
    //vector3d_add(self->position,self->position, self->velocity);
}

void fireball_update(Entity *self)
{        
    
}

/*eol@eof*/
