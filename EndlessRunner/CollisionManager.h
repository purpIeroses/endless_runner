#ifndef COLLISIONMANAGER_H_DEFINED
#define COLLISIONMANAGER_H_DEFINED
#include "Collider.h"
#include "Vector2.h"

struct CollisionManager
{
	CollisionManager();
	~CollisionManager();
	bool AABB(Collider one, Collider other);
};
#endif