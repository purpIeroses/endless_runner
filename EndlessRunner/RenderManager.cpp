#include "RenderManager.h"

HUDRenderObject::HUDRenderObject(Transform* trans, Sprite* sprite)
{
	m_trans = trans;
	m_sprite = sprite;
}

float RenderManager::shakeEnd()
{
	return shakeStart + shakeDuration;
}

float RenderManager::GetTime()
{
	return ((float)SDL_GetTicks()) * 0.001f;
}

inline float RenderManager::Cubic_EaseOut(float t, float b, float c, float d)
{
	return c * ((t = t / d - 1) * t * t + 1) + b;
}

int RenderManager::shakeX()
{
	float t = GetTime() - shakeStart;
	float b = cos(GetTime() * shakeSpeed) * shakeAmount;
	float c = -b;
	float d = shakeEnd() - shakeStart;

	if (t > d)return 0;


	float returnValue = Cubic_EaseOut(t, b, c, d);

	return (int)returnValue;
}

void RenderManager::Shake()
{
	shakeStart = GetTime();
}

RenderManager::RenderManager() : HUDRenderDimensions(0), RenderDimensions(0), m_renderer(nullptr), m_config(nullptr)
{
}

void RenderManager::Init(Screen& screen, Config* config)
{
	m_config = config;
	HUDRenderDimensions = m_config->HUDRenderDimensions;
	RenderDimensions = m_config->RenderDimensions;
	m_renderer = screen.renderer;
}

void RenderManager::AddToHUDRenderObjects(Sprite* sprite, Transform* trans)
{
	HUDrenderObjects.push_back(HUDRenderObject(trans, sprite));
}
void RenderManager::EmptyHUDRenderObjects()
{
	HUDrenderObjects.clear();
}
void RenderManager::RenderBackground(Sprite* sprite, Transform& trans)
{
	SDL_Rect dimensions = { (int)trans.m_position.x * RenderDimensions * 2 + shakeX(), (int)trans.m_position.y * RenderDimensions * 2,
		sprite->m_source.w * RenderDimensions*3, sprite->m_source.h * RenderDimensions *3};

	SDL_RenderCopy(m_renderer, sprite->m_texture, &sprite->m_source, &dimensions);
}
void RenderManager::Render(Sprite* sprite, Transform& trans)
{
	SDL_Rect dimensions = { (int)trans.m_position.x * RenderDimensions - 200 * (RenderDimensions - 1) + shakeX(), (int)trans.m_position.y * RenderDimensions - 700 * (RenderDimensions - 1),
		sprite->m_source.w * (int)m_config->RenderDimensions, sprite->m_source.h * (int)m_config->RenderDimensions };

	SDL_RenderCopy(m_renderer, sprite->m_texture, &sprite->m_source, &dimensions);
}
void RenderManager::Render(Rectangle& rect)
{
	SDL_Rect newRect{ rect.x * RenderDimensions - 200 * (RenderDimensions - 1), rect.y * RenderDimensions - 700 * (RenderDimensions - 1), rect.w * RenderDimensions, rect.h * RenderDimensions };
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
	SDL_RenderDrawRect(m_renderer, &newRect);
}
void RenderManager::RenderHUD()
{
	for (unsigned int i = 0; i < HUDrenderObjects.size(); i++)
	{
		OnRenderHUD(HUDrenderObjects[i].m_sprite, HUDrenderObjects[i].m_trans);
	}
}
void RenderManager::OnRenderHUD(Sprite* sprite, Transform* trans)
{
	SDL_Rect dimensions = { (int)trans->m_position.x * HUDRenderDimensions, (int)trans->m_position.y * HUDRenderDimensions, sprite->m_source.w * HUDRenderDimensions, sprite->m_source.h * HUDRenderDimensions};
	SDL_RenderCopy(m_renderer, sprite->m_texture, &sprite->m_source, &dimensions);
}

void RenderManager::OnQuit()
{
	m_config->HUDRenderDimensions = HUDRenderDimensions;
	m_config->RenderDimensions = RenderDimensions;
}