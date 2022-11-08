#include "simple_logger.h"
#include "gfc_types.h"

#include "gf3d_camera.h"
#include "player.h"

#include "gfc_primitives.h"

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
    ent->scale = vector3d(1,1,1);
    ent->bounds = gfc_box(1,1,1,10,10,10);
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
    camRight.x = j.y;
    camRight.y = -j.x;

    vector3d_set_magnitude(&camForward,0.15);
    vector3d_set_magnitude(&camRight,0.15);
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
        self->rotation.z = vector_angle(camForward.x, camForward.y) * GFC_DEGTORAD;  
        
    }
    if (keys[SDL_SCANCODE_D])
    {
        vector3d_add(self->position,self->position, camRight); 
        self->rotation.z = (vector_angle(camRight.x, camRight.y) + 180) * GFC_DEGTORAD;  

    }
    if (keys[SDL_SCANCODE_A])    
    {
        vector3d_add(self->position,self->position,-camRight);
        self->rotation.z = vector_angle(camRight.x, camRight.y) * GFC_DEGTORAD;  

    }
    if (keys[SDL_SCANCODE_SPACE] && self->canJump)
    {
        vector3d_add(self->position,self->position,vector3d(0,0,.5));
        self->canJump = 0;
    }
    else
    {
        self->canJump = 1;
    }

    if (keys[SDL_SCANCODE_Z])self->position.z -= 0.10;
    
    //player melee = e
    //if (keys[SDL_SCANCODE_Q]) meleeAttack(self);
    //player heavy = q
    //if (keys[SDL_SCANCODE_E]) ultAttack(self);

    
    //player rotation testing
    //if (keys[SDL_SCANCODE_Q])self->rotation.z -= 0.0050;
    //if (keys[SDL_SCANCODE_E])self->rotation.z += 0.0050;
    
    //camera pitch movement not needed
    //if (keys[SDL_SCANCODE_UP])self->camRotate.x -= 0.0050;
    //if (keys[SDL_SCANCODE_DOWN])self->camRotate.x += 0.0050;    
    
    //camera left and right movement
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
        rotation.x += M_PI*0.020;
        w = vector2d_from_angle(self->camRotate.z);
        forward.x = w.x * 100;
        forward.y = w.y * 100;
        vector3d_add(position,position,-forward);
    
    gf3d_camera_set_position(position);
    gf3d_camera_set_rotation(rotation);     
    
}

/*void meleeAttack(Entity *self)
{
    if(self->element == 1)
    {
        fireball_new();
    }

    if(self->element == 2)
    {
        ice_shard();
    }

    if(self->element == 3)
    {
        hypno_beam();
    }

    if(self->element == 4)
    {
        lightning();
    }

    if(self->element == 5)
    {
        wind_shove();
    }
}

void ultAttack(Entity *self)
{
    if(self->element == 1)
    {
        fire();
    }

    if(self->element == 2)
    {
        ice_shard();
    }

    if(self->element == 3)
    {
        hypno_beam();
    }

    if(self->element == 4)
    {
        lightning();
    }

    if(self->element == 5)
    {
        wind_shove();
    }
}*/

/*eol@eof*/
