#ifndef __ICESHARD_H__
#define __ICESHARD_H__

#include "entity.h"

/**
 * @brief Create a new player entity
 * @param position where to spawn the aguman at
 * @param direction where to shoot at
 * @return NULL on error, or an iceshard entity pointer on success
 */
Entity *iceshard(Vector3D position, Vector3D direction);


#endif