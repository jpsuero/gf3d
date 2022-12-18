#include "simple_logger.h"
#include "simple_json.h"
#include "gfc_types.h"

#include "world.h"
#include "enemy1.h"
#include "enemy2.h"

#include "enemy3.h"
#include "enemy4.h"
#include "enemy5.h"
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
            vector3d(10,50,1)
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
    enemy1_new(vector3d(-200,200,0), 6);
    enemy1_new(vector3d(200,200,0), 6);
    enemy1_new(vector3d(-200,-200,0), 6);
    enemy1_new(vector3d(200,-200,0), 6);

}
void level2()
{
    enemy2_new(vector3d(-200,200,0), 6);
    enemy2_new(vector3d(200,200,0), 6);
    enemy2_new(vector3d(-200,-200,0), 6);
    enemy2_new(vector3d(200,-200,0), 6);

}
void level3()
{
    enemy3_new(vector3d(-200,200,0), 6);
    enemy3_new(vector3d(200,200,0), 6);
    enemy3_new(vector3d(-200,-200,0), 6);
    enemy3_new(vector3d(200,-200,0), 6);

}
void level4()
{
    enemy4_new(vector3d(-200,200,0), 6);
    enemy4_new(vector3d(200,200,0), 6);
    enemy4_new(vector3d(-200,-200,0), 6);
    enemy4_new(vector3d(200,-200,0), 6);
}
void level5()
{
    enemy5_new(vector3d(-200,200,0), 6);
    enemy5_new(vector3d(200,200,0), 6);
    enemy5_new(vector3d(-200,-200,0), 6);
    enemy5_new(vector3d(200,-200,0), 6);

}
/*eol@eof*/
