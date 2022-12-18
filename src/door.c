#include "simple_logger.h"
#include "gfc_types.h"

//#include "gf3d_camera.h"
#include "door.h"
#include "world.h"

void door_think(Entity *self);
void door_update(Entity *self);


Entity *door_new(Vector3D position, int gateway)
{
    Entity *ent = NULL;
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no gateway for you!");
        return NULL;
    }
    
    ent->model = gf3d_model_load("cube");
    ent->think = door_think;
    ent->update = door_update;
    
    //ent->camRotate.x = M_PI;
    //ent->rotation.x = -M_PI;
    //ent->rotation.y = -M_PI;
    ///ent->gravity = vector3d(0, 0, -.1);
    //ent->canJump = 1;
    ent->scale = vector3d(10,10,50);
    ent->bounds = gfc_box(position.x,position.y,position.z,100,100,200);
    ent->circle = gfc_sphere(position.x,position.y,position.z, 6);
    vector3d_copy(ent->position,position);
    return ent;
}


void door_think(Entity *self)
{
    Entity * player = getPlayer();
    if(player ==NULL)return;


    if(gfc_point_in_sphere(player->position, self->circle))
    {
        switch(self->tag)
        {
            case 1:
            {
                player->level = 1;
                world_delete(getLevel());
                world_load("config/testworld1.json");
                player->position = vector3d(0,0,0);
                level1();
                slog("player colliding door 1");
                break;
            }
            case 2 :
            {
                player->level = 2;
                world_delete(getLevel());
                world_load("config/testworld2.json");
                player->position = vector3d(0,0,0);
                level2();
                slog("player colliding door 2");
                break;

            }
            case 3:
            {
                player->level = 3;
                world_delete(getLevel());
                world_load("config/testworld3.json");
                player->position = vector3d(0,0,0);
                level3();
                slog("player colliding door 3");
                break;

            }
            case 4:
            {
                player->level = 4;
                world_delete(getLevel());
                world_load("config/testworld4.json");
                player->position = vector3d(0,0,0);
                level4();
                slog("player colliding door 4");
                break;

            }
            case 5:
            {
                player->level = 5;
                world_delete(getLevel());
                world_load("config/testworld5.json");
                player->position = vector3d(0,0,0);
                level5();
                slog("player colliding door 5");
                break;

            }
        }
        
    }
    else
    {
        //slog("buttcheeks");
    }

    switch(self->tag)
    {
        case 1:
        {
            gf3d_model_free(self->model);
            self->model = gf3d_model_load("cube1");
            break;
        }
        case 2 :
        {
            gf3d_model_free(self->model);
            self->model = gf3d_model_load("cube2");
            break;
        }
        case 3:
        {
            gf3d_model_free(self->model);
            self->model = gf3d_model_load("cube3");  
            break;
        }
        case 4:
        {
            gf3d_model_free(self->model);
            self->model = gf3d_model_load("cube4");  
            break;
        }
    }
}
void door_update(Entity *self)
{        
    
}

/*eol@eof*/
