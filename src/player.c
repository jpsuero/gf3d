#include "simple_logger.h"
#include "gfc_types.h"

#include "gf3d_camera.h"
#include "player.h"

void player_think(Entity *self);
void player_update(Entity *self);


Entity *player_new(Vector3D position)
{
    Entity *ent = NULL;
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }
    
    ent->model = gf3d_model_load("dino");
    ent->think = player_think;
    ent->update = player_update;
    vector3d_copy(ent->position,position);
    ent->camRotate.x = M_PI;
    ent->rotation.x = -M_PI;
    ent->rotation.y = -M_PI;
    ent->gravity = vector3d(0, 0, -.1);
    ent->canJump = 1;
    return ent;
}


void player_think(Entity *self)
{
    Vector3D forward;
    Vector3D camForward = {0};
    Vector3D camRight = {0};
    Vector3D right;
    Vector3D up;
    Vector2D j;
    
    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

    vector3d_angle_vectors(self->rotation, &forward, &right, &up);
    vector3d_set_magnitude(&forward,0.1);
    vector3d_set_magnitude(&right,0.1);
    vector3d_set_magnitude(&up,0.1);
    j = vector2d_from_angle(self->camRotate.z);
    camForward.x = j.x;
    camForward.y = j.y;
    camRight.x = j.x-GFC_HALF_PI;
    camRight.y = j.y-GFC_HALF_PI;

    //CONSTANT GRAVITY

    if(self->position.z > 0)
    {
        vector3d_add(self->position,self->position, self->gravity);
    }
    if (keys[SDL_SCANCODE_W])
    {   
        vector3d_add(self->position,self->position, camForward);
        self->rotation.z = self->camRotate.z;  
    }
    if (keys[SDL_SCANCODE_S])
    {
        vector3d_add(self->position,self->position,-camForward);  

    }
    if (keys[SDL_SCANCODE_D])
    {
        vector3d_add(self->position,self->position,camRight); 
    }
    if (keys[SDL_SCANCODE_A])    
    {
        vector3d_add(self->position,self->position,-right);
    }
    if (keys[SDL_SCANCODE_SPACE] && self->canJump)
    {
        vector3d_add(self->position,self->position,vector3d(0,0,1));
        self->canJump = 0;
    }
    else
    {
        self->canJump = 1;
    }

    if (keys[SDL_SCANCODE_Z])self->position.z -= 0.10;
    

    if (keys[SDL_SCANCODE_Q])self->rotation.z -= 0.0050;
    if (keys[SDL_SCANCODE_E])self->rotation.z += 0.0050;
    
    if (keys[SDL_SCANCODE_UP])self->camRotate.x -= 0.0050;
    if (keys[SDL_SCANCODE_DOWN])self->camRotate.x += 0.0050;    
    if (keys[SDL_SCANCODE_RIGHT])self->camRotate.z -= 0.0050;
    if (keys[SDL_SCANCODE_LEFT])self->camRotate.z += 0.0050;
    
}

void player_update(Entity *self)
{       
    
    Vector3D forward = {0};
    Vector3D position;
    Vector3D rotation;
    Vector2D w;
    
    if (!self)return;
    
    vector3d_copy(position,self->position);
    vector3d_copy(rotation,self->camRotate);
        position.z += 30;
        rotation.x += M_PI*0.125;
        w = vector2d_from_angle(self->camRotate.z);
        forward.x = w.x * 100;
        forward.y = w.y * 100;
        vector3d_add(position,position,-forward);
    
    gf3d_camera_set_position(position);
    gf3d_camera_set_rotation(rotation);     
    
}

/*eol@eof*/
