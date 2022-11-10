#ifndef __morphELEMENT_H__
#define __morphELEMENT_H__

#include "entity.h"

/**
 * @brief Create a new enemy entity
 * @param position where to spawn the enemy at
 * @return NULL on error, or an enemy entity pointer on success
 */
Entity *morph_element_new(Vector3D position);

#endif 