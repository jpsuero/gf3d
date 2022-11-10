#ifndef __ENEMY3_H__
#define __ENEMY3_H__

#include "entity.h"

/**
 * @brief Create a new enemy entity
 * @param position where to spawn the enemy at
 * @param tag to identify enemy
 * @return NULL on error, or an enemy entity pointer on success
 */
Entity *enemy3_new(Vector3D position, int tag);

#endif 