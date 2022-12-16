#ifndef __VOIDELEMENT_H__
#define __VOIDELEMENT_H__

#include "entity.h"

/**
 * @brief Create a new enemy entity
 * @param position where to spawn the enemy at
 * @return NULL on error, or an enemy entity pointer on success
 */
Entity *void_element_new(Vector3D position);

#endif 