#include "platform.h"
#include "simple_json.h"
#include "simple_logger.h"
#include "gfc_primitives.h"
#include "gfc_types.h"
#include "entity.h"

void platform_think(Entity *self);
void platform_update(Entity *self);


Entity *platform_new(Vector3D position, int type, int level)
{
    Entity *ent = NULL;
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no platform for you!");
        return NULL;
    }

    if(type == 0)
    {
        ent->model = gf3d_model_load("cube2");
    }
    else if(type == 2)
    {
        ent->model = gf3d_model_load("cube2");
    }
    else if(type == 3)
    {
        ent->model = gf3d_model_load("cube4");
    }
    else if(type == 1)
    {
        ent->model = gf3d_model_load("cube1");
    }
    else if(type == 5)
    {
        ent->model = gf3d_model_load("cube");
    }
    else if(type == 6)
    {
        ent->model = gf3d_model_load("cube3");
    }
    else if(type == 7)
    {
        ent->model = gf3d_model_load("cube1");
    }
    else if(type == 8)
    {
        ent->model = gf3d_model_load("cube4");
    }
    else if(type == 9)
    {
        ent->model = gf3d_model_load("cube2");
    }
    else if(type == 11)
    {
        ent->model = gf3d_model_load("cube4");
    }
    else if(type == 12)
    {
        ent->model = gf3d_model_load("cube10");
    }
    else if(type == 15)
    {
        ent->model = gf3d_model_load("cube1");
    }
    else if(type == 16)
    {
        ent->model = gf3d_model_load("cube1");
    }


    vector3d_copy(ent->position,position);
    ent->think = platform_think;
    ent->update = platform_update;
    ent->scale = vector3d(25,25,5);
    ent->platformType = type;
    ent->level = level;
    ent->shocked = 0;
    ent->tag = 3;
    return ent;
}


void platform_think(Entity *self)
{
    Entity * player = getPlayer();
    Vector3D position;
    if(!self)return;
    if(!player)return;

    if(self->level != player->level)
    {
        entity_free(self);
    }

    vector3d_copy(position,self->position);
    
    if(self->platformType == 0)
    {
        self->scale = vector3d(100,100,1);
        self->bounds = gfc_box(position.x-100, self->position.y-100, position.z,200,200,3);
    }
    else
    {
        self->bounds = gfc_box(position.x-25, self->position.y-25, position.z-5,50,50,10);
    }

    if(self->platformType == 6)
    {
        self->bounds = gfc_box(position.x-12, self->position.y-12, position.z-50,25,25,100);
        self->scale = vector3d(10, 10, 40);
        if(gfc_box_overlap(self->bounds, player->bounds))
            {
                player->health--;
            }
    }

    
    //side to side movement
    if(self->platformType == 2)
    {    
        self->buffer++;
        if(self->buffer <= 300)
        {
            self->position.x +=.1;
            if(gfc_box_overlap(self->bounds, player->bounds))
            {
                player->position.x += .1;
            }
        }
        else if(self->buffer>=300 && self->buffer < 900)
        {
            self->position.x -= .1;
            if(gfc_box_overlap(self->bounds, player->bounds))
            {
                player->position.x -= .1;
            }
        }
        else 
        {
            self->buffer =-300;
        }
    }

    //river level
    if(self->platformType == 5)
    {   
        self->scale = vector3d(50,25,1);
        self->bounds = gfc_box(position.x-75, self->position.y-50, position.z,150,100,5);
        
        
        self->buffer++;
        if(self->buffer >=100)
        {
            self->position.y +=.1;
            if(gfc_box_overlap(self->bounds, player->bounds))
            {
                player->position.y += .1;
            }
        }
    }


    //falling platforms
    if(self->platformType == 3)
    {
        if(gfc_box_overlap(self->bounds, player->bounds))
        {
            self->buffer++;
        }
        if(self->buffer >= 400)
        {
            self->position.z -= 1;
        }
    }
    //battle ground
    if(self->platformType ==7)
    {
        self->scale = vector3d(500,500,1);
        self->bounds = gfc_box(position.x-500, self->position.y-500, position.z,1000,1000,3);
    }

    //water
    if(self->platformType == 8)
    {
        self->tag = 10;
        self->rotation.x = -GFC_HALF_PI;
        self->rotation.z = -GFC_HALF_PI;
        self->scale = vector3d(1000, 100, 50);
        self->bounds = gfc_box(position.x-1000, self->position.y-100, position.z-50,2000,200,100);
        if(!self->isFrozen)
        {
            if(gfc_box_overlap(self->bounds, player->bounds))
            {
                //drown player
                slog("player is drowning");
                player->position.z -=.05;
            }
        }
        else
        {
            gf3d_model_free(self->model);
            self->model = gf3d_model_load("cube9");
        }
    }
    //waterfall
    if(self->platformType == 11)
    {
        Entity* collider = NULL;

        self->tag = 10;
        self->scale = vector3d(50, 100, 1000);
        self->bounds = gfc_box(position.x-50, self->position.y-100, position.z-500,100,200,2000);
        if(!self->isFrozen)
        {
            if(gfc_box_overlap(self->bounds, player->bounds))
            {
                //drown player
                slog("player is drowning");
                player->position.z -=.05;
            }
        }
        else
        {
            gf3d_model_free(self->model);
            self->model = gf3d_model_load("cube9");
            collider = groundCheck(self);
            if(collider != NULL)
            {
                if(collider->tag == 10)
                {
                    if(self->isFrozen)
                    {
                        collider->isFrozen = 1;
                    }
                }
            }
        }
    }


    //elevator platforms
    if(self->platformType == 9)
    {
        self->buffer++;
        if(self->buffer <= 3000)
        {
            self->position.z +=.1;
            if(gfc_box_overlap(self->bounds, player->bounds))
            {
                player->position.z += .1;
            }
        }
        else if(self->buffer>=3000 && self->buffer < 6000)
        {
            self->position.z -= .1;
            if(gfc_box_overlap(self->bounds, player->bounds))
            {
                player->position.z -= .1;
            }
        }
        else 
        {
            self->buffer =0;
        }
    }

    //trigger platforms
    if(self->platformType == 15)
    {
        if(self->shocked)
        {
            player->trigger1 = 1;
        }
        else
        {
            player->trigger1 = 0;
        }
    }
    if(self->platformType == 16)
    {
        if(self->shocked)
        {
            self->rotation.x += .0050;
            self->rotation.y += .0050;
            self->rotation.z += .0050;
            player->trigger1 = 0;
        }
        else
        {
            self->rotation.x += .0050;
            self->rotation.y += .0050;
            self->rotation.z += .0050;
            player->trigger2 = 0;
        }
    }


}

void platform_update(Entity *self)
{        
    
}

/*eol@eof*/
