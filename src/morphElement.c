#include "simple_logger.h"
#include "gfc_types.h"
#include "morphElement.h"

void morph_element_think(Entity *self);
void morph_element_update(Entity *self);


Entity *morph_element_new(Vector3D position)
{
    Entity *ent = NULL;
    
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no enemy1 for you!");
        return NULL;
    }
    
    ent->model = gf3d_model_load("dino4");
    ent->think = morph_element_think;
    ent->update = morph_element_update;
    vector3d_copy(ent->position,position);
    //vector3d_copy(ent->velocity,direction);
    ent->scale = vector3d(.75,.75,.75);
    return ent;
}


void morph_element_think(Entity *self)
{
    Entity *player = NULL; 
    self->rotation.z += .0025;

    player=getPlayer();
    self->circle = gfc_sphere(self->position.x, self->position.y,self->position.z, 5);


    if(gfc_point_in_sphere(getPlayer()->position, self->circle))
    {
        player->dark=1;
        player->element=4;
        gf3d_model_free(player->model);
        player->model = gf3d_model_load("dino4");
        player->scale = vector3d(3,3,3);
        entity_free(self);
    }

}

void morph_element_update(Entity *self)
{        
    
}

/*eol@eof*/
