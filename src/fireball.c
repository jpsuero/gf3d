#include "simple_logger.h"
#include "gfc_types.h"

//#include "gf3d_camera.h"
#include "fireball.h"
#include "entity.h"

void fireball_think(Entity *self);
void fireball_update(Entity *self);


Entity *fireball(Vector3D position, Vector3D direction, int team)
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
    ent->gravity = vector3d(0,0, 0);
    ent->team = team;
    return ent;
}


void fireball_think(Entity *self)
{
    Entity * collider = NULL;
    Entity * player = getPlayer();
    if (!self)return;

    self->lifespan++;
    self->rotation.x += .0050;
    self->rotation.y += .0050;
    self->rotation.z += .0050;

    self->circle = gfc_sphere(self->position.x, self->position.y,self->position.z, 5);

    if(self->lifespan > 5000)
    {
        entity_free(self);
        return;
    }

    if(gfc_point_in_sphere(player->position, self->circle)&& self->team == 2)
    {
        player->health--;
        entity_free(self);
        return;
    }
    
    
    collider = collisionCheck(self);
    if(collider != NULL && self->team == 1)
    {
        if(collider->tag == 6)
        {
            switch(player->level)
            {
                case 1:
                {
                    entity_free(collider);
                    entity_free(self);
                    player->electricKill++;
                    break;
                }
                case 2:
                {
                    entity_free(collider);
                    entity_free(self);
                    player->fireKill++;
                    break;
                }
                case 3:
                {
                    entity_free(collider);
                    entity_free(self);
                    player->morphKill++;
                    break;
                }
                case 4:
                {
                    entity_free(collider);
                    entity_free(self);
                    player->darkKill++;
                    break;
                }
                case 5:
                {
                    entity_free(collider);
                    entity_free(self);
                    player->iceKill++;
                    break;
                }
        
            }
            entity_free(collider);
            entity_free(self);
        }
    }

    //vector3d_add(self->position,self->position, self->velocity);
}

void fireball_update(Entity *self)
{        
    
}

/*eol@eof*/
