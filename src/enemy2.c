#include "simple_logger.h"
#include "gfc_types.h"
#include "enemy2.h"
#include "fireball.h"

void enemy2_think(Entity *self);
void enemy2_update(Entity *self);


Entity *enemy2_new(Vector3D position, int tag)
{
    Entity *ent = NULL;
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no enemy2 for you!");
        return NULL;
    }
    
    ent->model = gf3d_model_load("cube2");
    ent->think = enemy2_think;
    ent->update = enemy2_update;
    vector3d_copy(ent->position,position);
    //vector3d_copy(ent->velocity,direction);
    ent->scale = vector3d(5,5,5);
    ent->circle = gfc_sphere(position.x,position.y,position.z, 5);
    ent->shootBuffer = 0;
    ent->health = 3;
    ent->tag = tag;
    return ent;
}


void enemy2_think(Entity *self)
{
    //self->rotation.x += .0050;
    //self->rotation.y += .0050;
    //self->rotation.z += .0050;

    Vector2D direction;
    Vector3D target = getPlayer()->position;
    direction.x = target.x - self->position.x;
    direction.y = target.y - self->position.y;
    vector2d_set_magnitude(&direction,.1);

    if(getPlayer()->level != 2)entity_free(self);

    self->shootBuffer++;
    if(self->shootBuffer == 10 && self->isFrozen == 0)
    {
        fireball(self->position, vector3d(direction.x, direction.y, 0), 2);
    }
    if(self->shootBuffer > 5000)self->shootBuffer =0;

    if(self->shocked == 1)
    {
        self->scale.x +=.01;
        self->scale.y +=.01;
        self->scale.z +=.01;
        self->rotation.x += .050;
        self->rotation.y += .050;
        self->rotation.z += .050;
        if(self->scale.z > 20)
        {
            entity_free(self);
        }
    }

}

void enemy2_update(Entity *self)
{        
    
}

/*eol@eof*/
