#include "simple_logger.h"
#include "gfc_types.h"

//#include "gf3d_camera.h"
#include "lightning.h"
#include "entity.h"

void lightning_think(Entity *self);
void lightning_update(Entity *self);


Entity *lightning(Vector3D position,  Vector3D direction, int team)
{
    Entity *ent = NULL;
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no lightning for you!");
        return NULL;
    }
    
    ent->model = gf3d_model_load("dino1");
    ent->think = lightning_think;
    ent->update = lightning_update;
    vector3d_copy(ent->position,position);
    vector3d_copy(ent->velocity,direction);
    ent->scale = vector3d(.5,.5,.5);
    ent->team = team;
    return ent;
}


void lightning_think(Entity *self)
{
    Entity * collider = NULL;
    Entity * collider2 = NULL;
    if (!self)return;
    
    self->lifespan++;
    self->rotation.x += .0050;
    self->rotation.y += .0050;
    self->rotation.z += .0050;

    if(self->lifespan > 5000)
    {
        entity_free(self);
    }

    collider = collisionCheck(self);
    if(collider != NULL && self->team == 1)
    {
        if(collider->tag == 6)
        {
            collider->shocked =1;
            entity_free(self);
        }
    }

    collider2 = groundCheck(self);
    if(collider2 != NULL)
    {
        if(collider2->tag == 10)
        {
            slog("trigger enabled");
            collider2->shocked =1;
        }
    }

    //vector3d_add(self->position,self->position, self->velocity);
}

void lightning_update(Entity *self)
{        
    
}

/*eol@eof*/
