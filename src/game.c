#include <SDL.h>     
#include <SDL_mixer.h>       

#include "simple_logger.h"
#include "gfc_input.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"
#include "gf3d_draw.h"
#include "gf3d_sprite.h"

//#include "gf2d_sprite.h"
#include "gf2d_font.h"
#include "gf2d_draw.h"

//audio
#include "gfc_audio.h"


#include "entity.h"
#include "agumon.h"
#include "player.h"
#include "world.h"
#include "door.h"
#include "enemy1.h"
#include "fireElement.h"
#include "iceElement.h"
#include "electricElement.h"
#include "voidElement.h"
#include "morphElement.h"


extern int __DEBUG;

int main(int argc,char *argv[])
{
    int exit = 0;
    int done = 1;
    int main = 1;
    int startButtonCollide = 0;
    int exitButtonCollide = 0;
    int a;

    //audio
    Mix_Music* music;
    
    Sprite *mouse = NULL;
    Sprite *element = NULL;
    Sprite *menu = NULL;
    int mousex,mousey;
    float mouseFrame = 0;
    World *w;
    
    for (a = 1; a < argc;a++)
    {
        if (strcmp(argv[a],"--debug") == 0)
        {
            __DEBUG = 1;
        }
    }
    
    init_logger("gf3d.log");    
    gfc_input_init("config/input.cfg");
    slog("gf3d begin");
    gf3d_vgraphics_init("config/setup.cfg");
    slog_sync();
    
    entity_system_init(1024);
    gfc_audio_init(256, 16, 4, 1, 1, 1);

    mouse = gf3d_sprite_load("images/pointer.png",32,32, 16);
    element = gf3d_sprite_load("images/fire.png", 1920,1080, 1);
    menu = gf3d_sprite_load("images/menu.png", 2560, 1440, 1);
    
    
    w = world_load("config/testworld.json");
    
    slog_sync();
    gf3d_camera_set_scale(vector3d(1,1,1));
    Entity *player = player_new(vector3d(0,0,20));
    Entity *door1 = door_new(vector3d(-150, 0, 0), 1);
    door1->tag =1;
    Entity *door2 = door_new(vector3d(0, 150, 0), 2);
    door2->tag =2;
    Entity *door3 = door_new(vector3d(150, 0, 0), 3);
    door3->tag =3;
    Entity *door4 = door_new(vector3d(0, -150, 0), 4);
    door4->tag =4;
    Entity *door5 = door_new(vector3d(150, -150, 0), 5);
    door5->tag =5;
     
    //audio
    music = Mix_LoadMUS("music/finalboss.mp3");
    Mix_PlayMusic(music, -1);
    

    // main game loop
    slog("gf3d main loop begin");

    while(main)
    {
        
        //button collision check
        if(mousex <= 203 && mousex >= 85)
        {
            if(mousey <= 290 && mousey >= 218)
            {
                startButtonCollide =1;
                exitButtonCollide = 0;
            }
            else if(mousey <= 387 && mousey >= 328)
            {
                exitButtonCollide = 1;
                startButtonCollide = 0;
            }
            else
            {
                exitButtonCollide = 0;
                startButtonCollide = 0;
            }
        }



        gfc_input_update();
        SDL_GetMouseState(&mousex,&mousey);

        mouseFrame += 0.01;
        if (mouseFrame >= 16)mouseFrame = 0;
        gf3d_camera_update_view();
        gf3d_camera_get_view_mat4(gf3d_vgraphics_get_view_matrix());

        //start game
        if((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) && startButtonCollide)
        {
            Mix_HaltMusic();
            done = 0;
            main = 0;
        }

        //exit game
        if((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) && exitButtonCollide)
        {
            exit = 1;
            return 0;
        }

        gf3d_vgraphics_render_start();

            //2D draws
            gf3d_sprite_draw(menu,vector2d(0, 0),vector2d(1,1),1);
            gf3d_sprite_draw(mouse,vector2d(mousex,mousey),vector2d(2,2),(Uint32)mouseFrame);
        
        gf3d_vgraphics_render_end();


    }
    

    while(!done)
    {
        gfc_input_update();
        SDL_GetMouseState(&mousex,&mousey);
        
        mouseFrame += 0.01;
        if (mouseFrame >= 16)mouseFrame = 0;
        entity_think_all();
        entity_update_all();
        gf3d_camera_update_view();
        gf3d_camera_get_view_mat4(gf3d_vgraphics_get_view_matrix());

        
        music = Mix_LoadMUS("music/japan_music.mp3");
        Mix_PlayMusic(music, -1);

        //element dropper
        if(player)
        {
            switch(player->level)
            {
                case 1:
                {
                    if(player->electricKill >= 4 && player->electric==0 && player->electricElement ==0)
                    {
                        electric_element_new(vector3d(0,0,0));
                        player->electricElement =1;
                    }
                    break;
                }
                case 2:
                {
                    if(player->fire == 0 && player->fireElement==0)
                    {
                        fire_element_new(vector3d(10,10,0));
                        player->fireElement =1;
                    }
                }
                case 3:
                {
                    if(player->morphKill >= 4 && player->bulk==0 &&player->morphElement ==0)
                    {
                        morph_element_new(vector3d(0,0,0));
                        player->morphElement=1;
                    }
                }
                case 4:
                {
                    if(player->darkKill >= 4 && player->dark ==0 && player->darkElement==0)
                    {
                        void_element_new(vector3d(0,0,0));
                        player->darkElement=1;

                    }
                }
                case 5:
                {
                    if(player->iceKill >= 4 && player->ice ==0 && player->darkElement==0)
                    {
                        ice_element_new(vector3d(0,0,0));
                        player->darkElement=1;
                    }
                }
            }
        }
        //uichanger
        if(player)
        {
            switch(player->element)
            {
                case 0:
                {
                    element = gf3d_sprite_load("images/ice.png", 1920,1080, 1);
                    break;
                }
                case 2:
                {
                    element = gf3d_sprite_load("images/fire.png", 1920,1080, 1);
                    break;
                }
                case 3:
                {
                    element = gf3d_sprite_load("images/void.png", 1920,1080, 1);
                    break;
                }
                case 4:
                {
                    element = gf3d_sprite_load("images/wind.png", 1920,1080, 1);
                    break;
                }
                case 1:
                {
                    element = gf3d_sprite_load("images/lightning.png", 1920,1080, 1);
                    break;
                }
            }
        }

        //out of bounds
        if(player->position.x < -241)player->position.x += .5;
        if(player->position.x > 241)player->position.x -= .5;
    
        if(player->position.y < -241)player->position.y += .5;
    
        if(player->position.y > 241)player->position.y -= .5;

        // configure render command for graphics command pool
        // for each mesh, get a command and configure it from the pool
        gf3d_vgraphics_render_start();

            //3D draws
                world_draw(getLevel());
                entity_draw_all();
            //2D draws
                //gf3d_sprite_draw(mouse,vector2d(mousex,mousey),vector2d(2,2),(Uint32)mouseFrame);
                gf3d_sprite_draw(element,vector2d(0, 0),vector2d(1,1),1);
        
        gf3d_vgraphics_render_end();

        if (gfc_input_command_down("exit") || player->health<=0 || exit == 1)
        {
            slog("player has died");
            done = 1; // exit condition

        }
    }

    


    
    world_delete(w);
    
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());    
    //cleanup
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    gfc_sound_clear_all();
    slog("gf3d program end");
    slog_sync();
    return 0;
}




/*eol@eof*/
