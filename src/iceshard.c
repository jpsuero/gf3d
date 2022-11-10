#include "simple_logger.h"
#include "gfc_types.h"
#include "entity.h"

//#include "gf3d_camera.h"
#include "iceshard.h"

void iceshard_think(Entity *self);
void iceshard_update(Entity *self);


Entity *iceshard(Vector3D position,  Vector3D direction, int team)
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
    ent->team = team;
    return ent;
}


void iceshard_think(Entity *self)
{
    Entity * collider = NULL;
    if (!self)return;
    
    self->lifespan++;
    self->rotation.x += .0050;
    self->rotation.y += .0050;
    self->rotation.z += .0050;

    if(!self)return;
    
    self->circle = gfc_sphere(self->position.x, self->position.y, self->position.z, 3);

    if(gfc_point_in_sphere(getPlayer()->position, self->circle)&& self->team == 2 && getPlayer()->isFrozen ==0)
    {
        getPlayer()->isFrozen = 1;
        entity_free(self);
        return;
    }
    
    collider = collisionCheck(self);
    if(collider != NULL && self->team == 1)
    {
        if(collider->tag == 6)
        {
            collider->isFrozen = 1;
            entity_free(self);
        }
    }

    if(self->lifespan > 5000)
    {
        entity_free(self);
    }
    //vector3d_add(self->position,self->position, self->velocity);
}

void iceshard_update(Entity *self)
{        
    
}

/*eol@eof*/
