#ifndef GUIARROW_H_DEFINED
#define GUIARROW_H_DEFINED

#include "Transform.h"
#include "Sprite.h"
#include "RenderManager.h"
#include "GUIObject.h"

struct GUIArrow
{
	GUIArrow(Transform& trans, ImageLibrary& imageLibrary);
	Transform m_trans;
	Sprite m_sprite;
	bool m_active;
	GUIObject* currentObject;
	void Render(RenderManager& rM);
	void ToggleArrow();
	void Move();
};
#endif