#include "simple_logger.h"
#include "gfc_types.h"
#include "enemy1.h"

void enemy1_think(Entity *self);
void enemy1_update(Entity *self);


Entity *enemy1_new(Vector3D position)
{
    Entity *ent = NULL;
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no enemy1 for you!");
        return NULL;
    }
    
    ent->model = gf3d_model_load("cube1");
    ent->think = enemy1_think;
    ent->update = enemy1_update;
    vector3d_copy(ent->position,position);
    //vector3d_copy(ent->velocity,direction);
    ent->scale = vector3d(3,3,3);
    ent->tag = 2;
    ent->circle = gfc_sphere(position.x,position.y,position.z, 3);
    return ent;
}


void enemy1_think(Entity *self)
{
    self->rotation.x += .0050;
    self->rotation.y += .0050;
    self->rotation.z += .0050;

    if(self->lifespan > 10000)
    {
        entity_free(self);
    }
    //vector3d_add(self->position,self->position, self->velocity);
    
    /*if(gfc_point_in_sphere(getPlayer()->position, self->circle))
    {
        switch(self->tag)
        slog("player colliding door");
    }
    else
    {
        slog("buttcheeks");
    }*/
}

void enemy1_update(Entity *self)
{        
    
}

/*eol@eof*/
