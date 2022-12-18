#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "entity.h"

/**
 * @brief Create a new platform entity
 * @param position where to spawn the platform at
 * @return NULL on error, or an platform entity pointer on success
 */
Entity *platform_new(Vector3D position, int type);

#endif 