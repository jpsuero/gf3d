#ifndef __DOOR_H__
#define __DOOR_H__

#include "entity.h"

/**
 * @brief Create a new fire door entity
 * @param position where to spawn the aguman at
 * @param scaler scale for agumon
 * @return NULL on error, or an agumon entity pointer on success
 */
Entity *door_new(Vector3D position, int gateway);


#endif
