#include "simple_logger.h"
#include "gfc_types.h"

//#include "gf3d_camera.h"
#include "door.h"

void player_think(Entity *self);
void player_update(Entity *self);


Entity *door_new(Vector3D position,  int gateway)
{
    Entity *ent = NULL;
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no gateway for you!");
        return NULL;
    }
    
    ent->model = gf3d_model_load("cube");
    //ent->think = door_think;
    //ent->update = door_update;
    vector3d_copy(ent->position,position);
    //ent->camRotate.x = M_PI;
    //ent->rotation.x = -M_PI;
    //ent->rotation.y = -M_PI;
    ///ent->gravity = vector3d(0, 0, -.1);
    //ent->canJump = 1;
    ent->scale = vector3d(10,10,50);
    return ent;
}


void door_think(Entity *self)
{
    
}

void door_update(Entity *self)
{        
    
}

/*eol@eof*/
