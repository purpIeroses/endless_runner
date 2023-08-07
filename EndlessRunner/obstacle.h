#ifndef OBSTACLE_H_DEFINED
#define OBSTACLE_H_DEFINED


#include <stdint.h>
#include <random>
#include "Sprite.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "Rectangle.h"
#include "Collider.h"


struct obstacle
{
	obstacle();
	obstacle(RenderManager* in);
	void Start();
	void Update(float dt);
	void Render();
	Sprite sprite;
	Transform trans;
	Collider col;
	RenderManager* renderManager;
};

#endif
