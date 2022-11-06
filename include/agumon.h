#ifndef __AGUMON_H__
#define __AGUMON_H__

#include "entity.h"

/**
 * @brief Create a new agumon entity
 * @param position where to spawn the aguman at
 * @param scaler scale for agumon
 * @return NULL on error, or an agumon entity pointer on success
 */
Entity *agumon_new(Vector3D position, Vector3D scaler);


#endif
