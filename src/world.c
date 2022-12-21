#include "simple_logger.h"
#include "simple_json.h"
#include "gfc_types.h"

#include <stdio.h>
#include <stdlib.h>

#include "world.h"
#include "enemy1.h"
#include "enemy2.h"
#include "enemy3.h"
#include "enemy4.h"
#include "enemy5.h"
#include "platform.h"
#include "fireElement.h"
#include "iceElement.h"
#include "electricElement.h"
#include "voidElement.h"
#include "morphElement.h"
#include "door.h"
/*
typedef struct
{

    Model *worldModel;
    List *spawnList;        //entities to spawn
    List *entityList;       //entities that exist in the world
}World;
*/

static World *currentLevel = NULL;

World *world_load(char *filename)
{
    SJson *json,*wjson;
    World *w = NULL;
    const char *modelName = NULL;
    w = gfc_allocate_array(sizeof(World),1);
    if (w == NULL)
    {
        slog("failed to allocate data for the world");
        return NULL;
    }
    json = sj_load(filename);
    if (!json)
    {
        slog("failed to load json file (%s) for the world data",filename);
        free(w);
        return NULL;
    }
    wjson = sj_object_get_value(json,"world");
    if (!wjson)
    {
        slog("failed to find world object in %s world condig",filename);
        free(w);
        sj_free(json);
        return NULL;
    }
    modelName = sj_get_string_value(sj_object_get_value(wjson,"model"));
    if (modelName)
    {
        w->worldModel = gf3d_model_load((char *)modelName);
        gfc_matrix_identity(w->modelMat);
        gfc_matrix_scale(
            w->modelMat,
            vector3d(100,100,1)
        );
        gfc_matrix_translate(
            w->modelMat,
            vector3d(0,0,-20)
        );
    }
    else
    {
        slog("world data (%s) has no model",filename);
    }
    sj_free(json);
    currentLevel = w;
    return w;
}

void world_draw(World *world)
{
    if (!world)return;
    if (!world->worldModel)return;// no model to draw, do nothing
    gf3d_model_draw(world->worldModel,world->modelMat);
}

void world_delete(World *world)
{
    if (!world)return;
    gf3d_model_free(world->worldModel);
    free(world);
}

void world_run_updates(World *world);

void world_add_entity(World *world,Entity *entity);

World *getLevel()
{
    return currentLevel;
}

void level1()
{
    Entity * door = NULL;

    //first set of platforms
    for (int i = 1; i <11; i++)
    {
        platform_new(vector3d(0, 100*i, 0), 1, 1);
    }
    //side to side platform
    platform_new(vector3d(50, 1100, 0), 2, 1);
    //2nd set of platforms
    for (int i = 1; i <11; i++)
    {
        platform_new(vector3d(100, 100*i+1100, 0), 1, 1);
    }


    //level floor start
    platform_new(vector3d(0, 0, 0), 0, 1);
    //level floor end
    platform_new(vector3d(100, 2300, 0), 0, 1);

    fire_element_new(vector3d(100,2300,5));

    //door to level 2
    door = door_new(vector3d(100, 2400, 10), 2);
    door->tag =2;

    //enemy1_new(vector3d(-200,200,0), 6);
    //enemy1_new(vector3d(200,200,0), 6);
    //enemy1_new(vector3d(-200,-200,0), 6);
    //enemy1_new(vector3d(200,-200,0), 6);


}
void level2()
{
    platform_new(vector3d(0, 0, -10), 0, 2);


     Entity * door = NULL;

    //first set of platforms
    for (int i = 1; i <11; i++)
    {
        platform_new(vector3d(0, 100*i, 0), 1, 2);
    }
    //falling platforms
    for (int i = 1; i <11; i++)
    {
        if(i%2 ==0)
        {
            platform_new(vector3d(25, 100*i+1000, 0), 3, 2);
        }
        else
        {
            platform_new(vector3d(-25, 100*i+1000, 0), 3, 2);
        }
    }

    //side to side platform #2
    platform_new(vector3d(0, 2100, 0), 2, 2);


    //level floor end
    platform_new(vector3d(0, 2300, 0), 0, 2);

    electric_element_new(vector3d(0,2300,5));

    //door to level 3
    door = door_new(vector3d(0, 2400, 10), 2);
    door->tag =3;


    enemy2_new(vector3d(-200,200,0), 6);
    enemy2_new(vector3d(200,200,0), 6);
    enemy2_new(vector3d(-200,-200,0), 6);
    enemy2_new(vector3d(200,-200,0), 6);

}
void level3()
{
    Entity * door = NULL;
    
    platform_new(vector3d(0, 0, 0), 5, 3);
    
    for (int i = 1; i <11; i++)
    {   
        if(i%2 ==0)
        {
            platform_new(vector3d(40, 100*i+1000, 25), 6, 3);
            platform_new(vector3d(-40, 100*i+1000, 25), 6, 3);
        }
        else
        {
            platform_new(vector3d(0, 100*i+1000, 25), 6, 3);
        }
    }

    platform_new(vector3d(0, 2300, 0), 0, 3);

    //door to level 3
    door = door_new(vector3d(0, 2400, 10), 2);
    door->tag =4;

    morph_element_new(vector3d(0,2300,5));



    //enemy3_new(vector3d(-200,200,0), 6);
    //enemy3_new(vector3d(200,200,0), 6);
    //enemy3_new(vector3d(-200,-200,0), 6);
    //enemy3_new(vector3d(200,-200,0), 6);

}
void level4()
{
    //battle arena
    platform_new(vector3d(0, 0, 0), 7, 4);


    //water 
    platform_new(vector3d(0, 600, -50), 8, 4);
    //waterfall
    platform_new(vector3d(1000, 600, 0), 11, 4);

    //next stage
    platform_new(vector3d(0, 850, 0), 0, 4);
    
    //elevator
    platform_new(vector3d(0, 800, 0), 9, 4);
    
    //enemies
    enemy2_new(vector3d(-200,200,10), 6);
    enemy2_new(vector3d(200,200,10), 6);
    enemy2_new(vector3d(-200,-200,10), 6);
    enemy2_new(vector3d(200,-200,10), 6);
    
    enemy1_new(vector3d(-200,200,10), 6);
    enemy1_new(vector3d(200,200,10), 6);
    enemy1_new(vector3d(-200,-200,10), 6);
    enemy1_new(vector3d(200,-200,10), 6);

    enemy3_new(vector3d(-100,100,10), 6);
    enemy3_new(vector3d(100,100,10), 6);
    enemy3_new(vector3d(-100,-100,10), 6);
    enemy3_new(vector3d(100,-100,10), 6);

    //floor 2
    platform_new(vector3d(0, 600, 250), 0, 4);

    platform_new(vector3d(-500, 0, 250), 15, 4);

    platform_new(vector3d(500, 0, 250), 16, 4);

    platform_new(vector3d(0, 0, 250), 0, 4);





}
void level5()
{
    enemy5_new(vector3d(-200,200,0), 6);
    enemy5_new(vector3d(200,200,0), 6);
    enemy5_new(vector3d(-200,-200,0), 6);
    enemy5_new(vector3d(200,-200,0), 6);

}
/*eol@eof*/
