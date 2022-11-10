#ifndef __ENEMY5_H__
#define __ENEMY5_H__

#include "entity.h"

/**
 * @brief Create a new enemy entity
 * @param position where to spawn the enemy at
 * @return NULL on error, or an enemy entity pointer on success
 */
Entity *enemy5_new(Vector3D position, int tag);

#endif 