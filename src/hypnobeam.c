#include "simple_logger.h"
#include "gfc_types.h"

//#include "gf3d_camera.h"
#include "hypnobeam.h"

void hypnobeam_think(Entity *self);
void hypnobeam_update(Entity *self);


Entity *hypnobeam(Vector3D position,  Vector3D direction, int team)
{
    Entity *ent = NULL;
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no hypnobeam for you!");
        return NULL;
    }
    
    ent->model = gf3d_model_load("dino3");
    ent->think = hypnobeam_think;
    ent->update = hypnobeam_update;
    vector3d_copy(ent->position,position);
    vector3d_copy(ent->velocity,direction);
    ent->scale = vector3d(.5,.5,.5);
    ent->team = team;
    return ent;
}


void hypnobeam_think(Entity *self)
{
    Entity * collider = NULL;
    if (!self)return;
    
    self->lifespan++;
    self->rotation.x += .0050;
    self->rotation.y += .0050;
    self->rotation.z += .0050;

    self->circle = gfc_sphere(self->position.x, self->position.y,self->position.z, 5);

    if(self->lifespan > 5000)
    {
        entity_free(self);
    }

    if(gfc_point_in_sphere(getPlayer()->position, self->circle)&& self->team == 2)
    {
        getPlayer()->position = vector3d(0,0,0);
        entity_free(self);
        return;
    }
    
    
    collider = collisionCheck(self);
    if(collider != NULL && self->team == 1)
    {
        if(collider->tag == 6)
        {
            collider->position = vector3d(0, 0, 15);
            collider->inVoid = 1;
            collider->isFrozen = 1;
            entity_free(self);
        }
    }

    //vector3d_add(self->position,self->position, self->velocity);
}

void hypnobeam_update(Entity *self)
{        
    
}

/*eol@eof*/
