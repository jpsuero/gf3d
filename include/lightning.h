#ifndef __LIGHTNING_H__
#define __LIGHTNING_H__

#include "entity.h"

/**
 * @brief Create a new player entity
 * @param position where to spawn the lightning at
 * @param direction where to shoot at
 * @return NULL on error, or an lightning entity pointer on success
 */
Entity *lightning(Vector3D position, Vector3D direction, int team);


#endif