#include "simple_logger.h"
#include "gfc_types.h"
#include "fireElement.h"

void fire_element_think(Entity *self);
void fire_element_update(Entity *self);


Entity *fire_element_new(Vector3D position)
{
    Entity *ent = NULL;
    
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no enemy1 for you!");
        return NULL;
    }
    
    ent->model = gf3d_model_load("dino2");
    ent->think = fire_element_think;
    ent->update = fire_element_update;
    vector3d_copy(ent->position,position);
    //vector3d_copy(ent->velocity,direction);
    ent->scale = vector3d(.75,.75,.75);
    return ent;
}


void fire_element_think(Entity *self)
{
    Entity *player = NULL; 
    self->rotation.z += .0025;

    player=getPlayer();
    self->circle = gfc_sphere(self->position.x, self->position.y,self->position.z, 5);


    if(gfc_point_in_sphere(getPlayer()->position, self->circle))
    {
        player->fire=1;
        player->element=2;
        gf3d_model_free(player->model);
        player->model = gf3d_model_load("dino2");
        player->scale = vector3d(1,1,1);
        entity_free(self);
    }

}

void fire_element_update(Entity *self)
{        
    
}

/*eol@eof*/
