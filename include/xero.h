#ifndef __XERO_H__
#define __XERO_H__

#include "entity.h"

/**
 * @Creates new "Xero" entity
 * @param position where to spawn player at
 * @return NULL on error, or a Xero entity pointer on success
*/

Entity *xero_new(Vector3D position);


#endif