#ifndef BACKGROUNDELEMENT_H_DEFINED
#define BACKGROUNDELEMENT_H_DEFINED

#include "Transform.h"
#include "Sprite.h"
#include "RenderManager.h"

struct BackgroundElement
{
	RenderManager* renderManager;
	BackgroundElement(RenderManager* in, Sprite sprt);
	Transform trans;
	Sprite sprite;
	void MoveAtSpeed(float speed);
	void Render();
};
#endif