#ifndef __HYPNOBEAM_H__
#define __HYPNOBEAM_H__

#include "entity.h"

/**
 * @brief Create a new hypno entity
 * @param position where to spawn the hypno at
 * @param direction where to shoot at
 * @return NULL on error, or an hypno entity pointer on success
 */
Entity *hypnobeam(Vector3D position, Vector3D direction);


#endif