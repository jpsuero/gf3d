#include <SDL.h>            

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
//#include "gf3d_sprite.h"

#include "gf2d_sprite.h"
#include "gf2d_font.h"
#include "gf2d_draw.h"


#include "entity.h"
#include "agumon.h"
#include "player.h"
#include "world.h"
#include "door.h"
#include "enemy1.h"

extern int __DEBUG;

int main(int argc,char *argv[])
{
    int done = 0;
    int a;
    
    Sprite *mouse = NULL;
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
    
    mouse = gf2d_sprite_load("images/spritesheet.png",50,50, 1);
    
    w = world_load("config/testworld.json");
    
    /*for (a = 0; a < 10;a++)
    {
        agumon_new(vector3d(a * 10,0,0), vector3d(a,a,a));
    }
    */
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
    enemy1_new(vector3d(50,50,0));
     
    //player scale up
    

    // main game loop
    slog("gf3d main loop begin");
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

        //level changer
        //if(player)
        //{
        //    switch(player->level)
        //    {
        //        case 1:
        //        {
        //            world_delete(w);
        //            w = world_load("config/testworld1.json");
        //            slog("level changed");
        //            break;
        //        }
        //        case 2:
        //        {
        //            world_delete(w);
        //            w = world_load("config/testworld2.json");
        //            break;
        //        }
        //    }
        //}
        
    
        if(player->position.x < -241)player->position.x += .5;
        if(player->position.x > 241)player->position.x -= .5;
    
        if(player->position.y < -241)player->position.y += .5;
    
        if(player->position.y > 241)player->position.y -= .5;


        slog("%f", player->position.x);
        slog("%f", player->position.y);
        slog("%f", player->position.z);

        // configure render command for graphics command pool
        // for each mesh, get a command and configure it from the pool
        gf3d_vgraphics_render_start();

            //3D draws
                world_draw(getLevel());
                entity_draw_all();
                //gf3d_draw_cube_wireframe(player->bounds, player->position, player->rotation, vector3d(1,1,1), player->color);
            //2D draws
                gf3d_sprite_draw(mouse,vector2d(mousex,mousey),vector2d(2,2),vector3d(8,8,0),gfc_color(0.3,.9,1,0.9),(Uint32)mouseFrame);
        gf3d_vgraphics_render_end();

        if (gfc_input_command_down("exit"))done = 1; // exit condition
    }    
    
    world_delete(w);
    
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());    
    //cleanup
    slog("gf3d program end");
    slog_sync();
    return 0;
}


/*eol@eof*/
