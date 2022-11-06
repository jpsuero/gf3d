#include "simple_logger.h"
#include "gfc_types.h"

#include "gf3d_camera.h"
#include "xero.h"

void xero_think(Entity *self);
void xero_update(Entity *self);

Entity *xero_new(Vector3D position)
{
    Entity *ent = NULL;

    ent = entity_new();
    if(!ent)
    {
        slog("xero entity not found");
        return NULL;
    }
    ent->model = gf3d_model_load("dino");
    ent->think = xero_think;
    ent->update = xero_update;
    vector3d_copy(ent->position, position);
    ent->rotation.x = M_PI;
    return ent;
}

void xero_think(Entity *self)
{
    Vector3D forward;
    Vector3D right;
    Vector3D up;
    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

    vector3d_angle_vectors(self->rotation, &forward, &right, &up);
    vector3d_set_magnitude(&forward,0.1);
    vector3d_set_magnitude(&right,0.1);
    vector3d_set_magnitude(&up,0.1);

    if (keys[SDL_SCANCODE_W])
    {   
        vector3d_add(self->position,self->position,forward);
    }
    if (keys[SDL_SCANCODE_S])
    {
        vector3d_add(self->position,self->position,-forward);        
    }
    if (keys[SDL_SCANCODE_D])
    {
        vector3d_add(self->position,self->position,right);
    }
    if (keys[SDL_SCANCODE_A])    
    {
        vector3d_add(self->position,self->position,-right);
    }
    if (keys[SDL_SCANCODE_SPACE])self->position.z += 0.10;
    if (keys[SDL_SCANCODE_Z])self->position.z -= 0.10;
    
    if (keys[SDL_SCANCODE_UP])self->rotation.x -= 0.0050;
    if (keys[SDL_SCANCODE_DOWN])self->rotation.x += 0.0050;
    if (keys[SDL_SCANCODE_RIGHT])self->rotation.z -= 0.0050;
    if (keys[SDL_SCANCODE_LEFT])self->rotation.z += 0.0050;

}

void xero_update(Entity *self)
{
    if (!self)return;
    gf3d_camera_set_position(self->position);
    gf3d_camera_set_rotation(self->rotation);
}

/*eol@eof*/