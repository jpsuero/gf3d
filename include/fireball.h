#ifndef __FIREBALL_H__
#define __FIREBALL_H__

#include "entity.h"

/**
 * @brief Create a new player entity
 * @param position where to spawn the fireball at
 * @param direction where to shoot at
 * @param team team of projectile
 * @return NULL on error, or an fireball entity pointer on success
 */
Entity *fireball(Vector3D position, Vector3D direction, int team);


#endif