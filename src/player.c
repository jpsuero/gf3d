#include "simple_logger.h"
#include "gfc_types.h"

#include "gf3d_camera.h"
#include "player.h"

#include "gfc_primitives.h"
#include "iceshard.h"
#include "fireball.h"
#include "hypnobeam.h"
#include "lightning.h"
#include "entity.h"

void player_think(Entity *self);
void player_update(Entity *self);
void meleeAttack(Entity *self, Vector3D direction);
void slam(Entity *self);


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
    ent->gravity = vector3d(0, 0, -.05);
    ent->canJump = 1;
    ent->jumpCount = 0;
    ent->scale = vector3d(1,1,1);
    ent->bounds = gfc_box(1,1,1,10,10,10);
    ent->bigCircle = gfc_sphere(position.x, position.y, position.z, 100)
;    ent->color = gfc_color_from_vector4(vector4d(255,255,0,0));
    ent->tag = 0;
    ent->level = 0;
    ent->health = 5;
    return ent;
    
}


void player_think(Entity *self)
{
    Vector3D forward;
    Vector3D camForward = {0};
    Vector3D camRight = {0};
    Vector3D right;
    Vector3D up;
    Vector3D shoot;
    Vector2D j;
    Vector2D shootAngle;

    shootAngle = vector2d_from_angle(self->rotation.z);
    shoot = vector3d(shootAngle.x, shootAngle.y, 0);

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

    if(self->slamming ==1)
    {
        self->gravity = vector3d(0,0,-.1);
    }
    else
    {
        self->gravity = vector3d(0,0,-.05);
    }

    if(self->position.z > 0)
    {
        vector3d_add(self->position,self->position, self->gravity);
    }
    else
    {
        self->canJump = 1;
        self->jumpCount = 0;
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
    if (keys[SDL_SCANCODE_SPACE] && self->canJump && self->jumpCount == 0)
    {
        for (int i =0; i<1000; i++)
        {
            //vector3d_add(self->position,self->position,vector3d(0,0,.05));
            self->position.z += .025;
            
        }
        self->canJump = 0;
        self->jumpCount ++;
        slog("jump");
    }
    else if (!keys[SDL_SCANCODE_SPACE] && self->jumpCount == 1)
    {
        self->canJump = 1;
    }
    else if (keys[SDL_SCANCODE_SPACE] && self->jumpCount == 1 && self->canJump)
    {
        for (int i =0; i<1000; i++)
        {
            //self->rotation.x = .050;
            self->position.z += .025;
            //flip
            //self->rotation.x += 10;
            //vector3d_add(self->position,self->position,vector3d(0,0,.05));
            //slog("doublejump");
        }
        self->canJump = 0;
        self->jumpCount = 2;
    }
    
    

    if (keys[SDL_SCANCODE_Z])self->position.z -= 0.10;

    if(self->scale.z == .5)
    {
        self->squishBuffer++;
        if(self->squishBuffer >= 3000)
        {
            self->scale.z = 1;
            self->squishBuffer =0;
        }
    }

    //element changer
    if (keys[SDL_SCANCODE_6])
    {
        self->element = 0;
        gf3d_model_free(self->model);
        self->model = gf3d_model_load("dino");
        self->scale = vector3d(1,1,1);
    }
    if (keys[SDL_SCANCODE_7])
    {
        self->element = 1;
        gf3d_model_free(self->model);
        self->model = gf3d_model_load("dino1");
        self->scale = vector3d(1,1,1);
    }
    if (keys[SDL_SCANCODE_8])
    {
        self->element = 2;
        gf3d_model_free(self->model);
        self->model = gf3d_model_load("dino2");
        self->scale = vector3d(1,1,1);

    }
    if (keys[SDL_SCANCODE_9])
    {
        self->element = 3;
        gf3d_model_free(self->model);
        self->model = gf3d_model_load("dino3");
        self->scale = vector3d(1,1,1);
    }
    if (keys[SDL_SCANCODE_0])
    {
        self->element = 4;
        gf3d_model_free(self->model);
        self->model = gf3d_model_load("dino4");
        self->scale = vector3d(3,3,3);
    }

    if(self->element == 4)
    {
        if(self->position.z>0)
        {
            self->slamming =1;
        }
        else
        {
            self->slamming =0;
        }
    }
    
    //player melee = e
    if (keys[SDL_SCANCODE_E] && self->canAttack) 
    {
        meleeAttack(self, shoot);
        self->canAttack = 0;
    }
    if (!keys[SDL_SCANCODE_E]) self->canAttack = 1;
    
    //camera left and right movement
    if (keys[SDL_SCANCODE_RIGHT])self->camRotate.z -= 0.0050;
    if (keys[SDL_SCANCODE_LEFT])self->camRotate.z += 0.0050;
    

    //Entity *col = collisionCheck(self);
    //if(col)
    //{
    //    slog("is colliding");
    //}

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
        if(self->element != 4)
        {
            position.z += 30;
            rotation.x += M_PI*0.020;
        }
        else
        {
            position.z += 50;
            rotation.x += M_PI*0.030;
        }
        
        w = vector2d_from_angle(self->camRotate.z);
        forward.x = w.x * 100;
        forward.y = w.y * 100;
        vector3d_add(position,position,-forward);
    
 
    gf3d_camera_set_position(vector3d(position.x, position.y, 30));
    gf3d_camera_set_rotation(rotation);  
    
}

void meleeAttack(Entity *self, Vector3D direction)
{
    if(self->element == 2)
    {
        slog("shoot fireball");
        fireball(self->position, direction, 1);
    }

    if(self->element == 0)
    {
        slog("shoot iceshard");
        iceshard(self->position, direction, 1);
    }

    if(self->element == 3)
    {
        slog("shoot hypnobeam");
        hypnobeam(self->position, direction, 1);
    }

    if(self->element == 1)
    {
        slog("shoot lightning");
        lightning(self->position, direction);
    }
}




/*void ultAttack(Entity *self)
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
