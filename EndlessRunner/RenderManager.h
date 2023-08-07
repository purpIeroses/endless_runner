#ifndef RENDERMANAGER_H_DEFINED
#define RENDERMANAGER_H_DEFINED

#include <vector>
#include "Sprite.h"
#include "Rectangle.h"
#include "Screen.h"
#include "Transform.h"
#include "Config.h"

struct HUDRenderObject
{
	Transform* m_trans;
	Sprite* m_sprite;
	HUDRenderObject(Transform* trans, Sprite* sprite);
};

struct RenderManager
{
	Config* m_config;
	float HUDRenderDimensions;
	float RenderDimensions;
	const float shakeDuration = 1.5f;
	const float shakeAmount = 5.0f;
	const float shakeSpeed = 80.0f;
	float shakeStart = -FLT_MAX;
	float shakeEnd();
	static float GetTime();
	inline static float Cubic_EaseOut(float t, float b, float c, float d);
	int shakeX();
	void Shake();

	std::vector<HUDRenderObject> HUDrenderObjects;
	SDL_Renderer* m_renderer;

	RenderManager();

	void Init(Screen& screen, Config* config);
	void AddToHUDRenderObjects(Sprite* sprite, Transform* trans);
	void EmptyHUDRenderObjects();
	void RenderBackground(Sprite* sprite, Transform& trans);
	void Render(Sprite* sprite, Transform& trans);
	void Render(Rectangle& rect);
	void RenderHUD();
	void OnRenderHUD(Sprite* sprite, Transform* trans);
	void OnQuit();
}; 
#endif
