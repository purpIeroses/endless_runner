#ifndef GUIOBJECT_H_DEFINED
#define GUIOBJECT_H_DEFINED

#include "Sprite.h"
#include "Transform.h"
#include "ImageLibrary.h"
#include "Keycode.h"
#include "RenderManager.h"
#include "GameStateManager.h"
#include "HeliumMath.h"
#include <math.h>

enum GUIObjectState
{
	GOING_IN = 0,
	GOING_OUT = 1,
	STILL = 2
};

struct GUIObject
{
	float m_speed;
	GUIObjectState* p_state;
	GameStateManager* p_gM;
	Sprite m_sprite;
	Transform m_position;
	Transform m_offscreen;
	Transform m_menuscreen;
	float m_clock = 0.0f;
	float y;
	float x;
	GUIObject();
	GUIObject(Transform pos, Transform off, Transform menu, Sprite* sprite, GameStateManager* gM);
	void SetState(GUIObjectState* state);
	virtual bool Update(ImageLibrary& imageLibrary);
	virtual ~GUIObject();
	virtual void ToggleHighlight(bool value, ImageLibrary& imageLibrary);
	virtual void Render(RenderManager& rM);
	void Ease(Transform& from, Transform& to);
	virtual bool OnKeyDown(KeyCode key, RenderManager& renderManager);
	virtual bool OnClick(RenderManager& renderManager);
	virtual float GetArrowX();
};

#endif