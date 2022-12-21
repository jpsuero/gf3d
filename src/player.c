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
#include "gfc_audio.h"

void player_think(Entity *self);
void player_update(Entity *self);
void meleeAttack(Entity *self, Vector3D direction);
void addForce(Entity *self, Vector3D force);
void jump(Entity *self, Vector3D force);

Entity *player_new(Vector3D position)
{
    Entity *ent = NULL;
    const char * model = NULL;
    int health = 5;
    float grav = 0;


    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }

    SJson* json;
	json = sj_load("config/player.json");
    model = sj_get_string_value(sj_object_get_value(json,"model"));
    sj_get_integer_value(sj_object_get_value(json, "health"), &health);



    ent->model = gf3d_model_load((char *)model);
    ent->think = player_think;
    ent->update = player_update;
    vector3d_copy(ent->position,position);
    ent->camRotate.x = M_PI;
    ent->rotation.x = -M_PI;
    ent->rotation.y = -M_PI;
    ent->rotation.z = GFC_HALF_PI;
    ent->gravity = vector3d(0, 0, grav);
    ent->canJump = 1;
    ent->jumpCount = 0;
    ent->scale = vector3d(1,1,1);
    ent->bigCircle = gfc_sphere(position.x, position.y, position.z, 10000);
    ent->color = gfc_color_from_vector4(vector4d(255,255,0,0));
    ent->tag = 0;
    ent->level = 0;
    ent->health = health;
    ent->fire =0;
    ent->ice=0;
    ent->bulk=0;
    ent->electric=0;
    ent->dark=0;
    return ent;
    
}


void player_think(Entity *self)
{
    Entity *collider = NULL;
    Vector3D forward;
    Vector3D camForward = {0};
    Vector3D camRight = {0};
    Vector3D right;
    Vector3D up;
    Vector3D shoot;
    Vector2D j;
    Vector2D shootAngle;

    Sound * boing = gfc_sound_load("music/jump.wav", .5, 0);

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

    //player hitbox
    if(self->element!=4)
    {
        self->bounds = gfc_box(self->position.x-5, self->position.y-5, self->position.z-5, 10, 10, 10);
    }
    else
    {
        self->bounds = gfc_box(self->position.x-5, self->position.y-5, self->position.z-10, 10, 10, 10);
    }

    //groundcheck
    collider = groundCheck(self);
    if(collider != NULL)
        {
            if(collider->tag ==3 || collider->tag == 10)
            {
                self->isGrounded =1;
            }
        }
    else
    {
        self->isGrounded =0;
    }


    if(self->trigger1)
    {
        platform_new(vector3d(0, 400, 250), 1, 4);
    }

    if(self->trigger2)
    {
        platform_new(vector3d(0, 400, 250), 1, 4);
    }

    


    //flight for cheating
    if(keys[SDL_SCANCODE_Q])
    {
        self->position.z = 15;
    }
    
    //gravity
    if(self->isGrounded == 0)
    {
        self->acceleration.z = -.0025;
        //slog("not grounded");
    }
    else if(self->isGrounded == 1 && self->isDrowning == 0)
    {
        self->velocity.z =0;
        self->acceleration.z =0;
        self->canJump = 1;
        self->jumpCount = 0;
        //slog("grounded");
    }

    //player reset
    if(self->position.z <= -50)
    {
        self->position = vector3d(0,0,0);
    }

    //slam gravity
    if(self->slamming ==1)
    {
        self->gravity = vector3d(0,0,-.1);
    }
    else
    {
        self->gravity = vector3d(0,0,-.05);
    }
    
    
    //player movement
    if(self->isFrozen == 0)
    {

    
        if (keys[SDL_SCANCODE_W])
        {   
            addForce(self, camForward);
            //vector3d_add(self->position,self->position, camForward);
            self->rotation.z = self->camRotate.z;  
        }
        else
        {
            self->velocity.x = 0;
            self->velocity.y = 0;
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
            
            self->velocity.z = .5;
            
            //self->isJumping = 1;
            gfc_sound_play(boing, 0, 10, -1, -1);
            //old jump mechanics
            //for (int i =0; i<1000; i++)
            //{
            //    //vector3d_add(self->position,self->position,vector3d(0,0,.05));
            //    self->position.z += .025;
            //}
            self->canJump = 0;
            self->jumpCount ++;
            //slog("jump");
        }
        else if (!keys[SDL_SCANCODE_SPACE] && self->jumpCount == 1)
        {
            self->canJump = 1;
        }
        else if (keys[SDL_SCANCODE_SPACE] && self->jumpCount == 1 && self->canJump)
        {
            self->velocity.z = .5;
            //self->isJumping = 1;
            gfc_sound_play(boing, 0, 10, -1, -1);
            ////old dub jump
            //for (int i =0; i<1000; i++)
            //{
            //    self->position.z += .025;
            //}
            self->canJump = 0;
            self->jumpCount = 2;
        }
    }


    if(self->isJumping)
    {
        self->position.z+=.25;
        self->jumpBuffer++;
        if(self->jumpBuffer >= 100)
        {
            self->isJumping =0;
            self->jumpBuffer =0;
        }
    }
    

    if(self->isSquished)
    {
        self->scale.z = .5;
        self->squishBuffer++;
        if(self->squishBuffer >= 3000)
        {
            self->scale.z = 1;
            self->isSquished = 0;
            self->squishBuffer =0;
        }
    }
    if(self->isFrozen == 1)
    {
        self->frozenBuffer++;
        if(self->frozenBuffer >= 3000)
        {
            self->frozenBuffer =0;
            self->isFrozen =0;
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
        self->slamming = 1;
    }
    else
    {
        self->slamming = 0;
    }
    
    if(self->isFrozen == 0)
    {
        //player melee = e
        if (keys[SDL_SCANCODE_E] && self->canAttack) 
        {
            meleeAttack(self, shoot);
            self->canAttack = 0;
        }
        if (!keys[SDL_SCANCODE_E]) self->canAttack = 1;
    }
    //camera left and right movement
    if (keys[SDL_SCANCODE_RIGHT])self->camRotate.z -= 0.00250;
    if (keys[SDL_SCANCODE_LEFT])self->camRotate.z += 0.00250;

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
            rotation.x += M_PI*0.050;
        }
        
        w = vector2d_from_angle(self->camRotate.z);
        forward.x = w.x * 100;
        forward.y = w.y * 100;
        vector3d_add(position,position,-forward);
    
 
    gf3d_camera_set_position(vector3d(position.x, position.y, position.z));
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
        lightning(self->position, direction, 1);
    }
}

void addForce(Entity * ent, Vector3D force)
{
    ent->velocity.x = force.x;
    ent->velocity.y = force.y;
    //ent->velocity.z = force.z;
}


void jump(Entity * ent, Vector3D jumpForce)
{
    for(int i = 0; i<= 300; i++)
    {
        ent->position.z += .1;
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
