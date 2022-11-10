#include "simple_logger.h"
#include "gfc_types.h"
#include "enemy1.h"
#include "lightning.h"

void enemy1_think(Entity *self);
void enemy1_update(Entity *self);


Entity *enemy1_new(Vector3D position, int tag)
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
    ent->tag = tag;
    ent->isFrozen = 0;
    ent->inVoid = 0;
    return ent;
}


void enemy1_think(Entity *self)
{

    if(getPlayer()->level != 1)entity_free(self);

    Vector2D direction;
    Vector3D target = getPlayer()->position;
    direction.x = target.x - self->position.x;
    direction.y = target.y - self->position.y;
    if(self->isFrozen == 0 && self->shocked ==0)
    {
        vector2d_set_magnitude(&direction,.1);
        self->velocity = vector3d(direction.x, direction.y, 0);
        self->rotation.x += .0050;
        self->rotation.y += .0050;
        self->rotation.z += .0050;
        
    }
    else
    {   
        vector2d_set_magnitude(&direction,0);
        self->velocity = vector3d(direction.x, direction.y, 0);
    }
    self->circle = gfc_sphere(self->position.x, self->position.y,self->position.z, 5);


    if(gfc_point_in_sphere(getPlayer()->position, self->circle))
    {
        if(getPlayer()->slamming== 0)
        {
            entity_free(self);
            getPlayer()->health--;
        }
        else
        {
            self->isFrozen=1;
            self->scale.z = .5;
        }
        
    }

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

    //vector3d_move_towards(&self->velocity, self->position, target, 1);
    
    //vector3d_add(self->position,self->position, target->position);
    
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
