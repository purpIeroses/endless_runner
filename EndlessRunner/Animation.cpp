#include "Animation.h"

Animation::Animation() : m_frames(0), m_index(0), m_sprite(Sprite()), m_animationtype(0)
{ }

Animation::Animation(int frames, int index, SDL_Texture* m_texture, RenderManager* rm, ImageLibrary& imageLibrary, int animationtype)
{
	m_animationtype = animationtype;
}

Sprite Animation::GetSprite()
{
	return m_sprite;
}

bool Animation::Update(Uint32 dt, SceneManager& sceneManager, ImageLibrary& imageLibrary, MetaManager* m_mM)
{
	m_sprite.m_source.x = m_sprite.m_source.w * ((dt / 100) % m_frames);
	return true;
}

WalkAnimation::WalkAnimation(){}

WalkAnimation::WalkAnimation(int frames, int index, SDL_Texture* m_texture, RenderManager* rm, ImageLibrary& imageLibrary)
{
	m_frames = frames;
	m_index = index;
	m_sprite.m_surface = imageLibrary.surfaces[m_index];
	m_sprite.m_texture = m_texture;
	m_sprite.SetSource(0, 0, imageLibrary.surfaces[m_index]->w / m_frames, imageLibrary.surfaces[m_index]->h);
	m_sprite.SetDestination(200, 700 - 16, m_sprite.m_source.w, m_sprite.m_source.h);
}

bool WalkAnimation::Update(Uint32 dt, SceneManager& sceneManager, ImageLibrary& imageLibrary, MetaManager* m_mM)
{
	m_sprite.m_source.x = m_sprite.m_source.w * ((dt / 100) % m_frames);
	return true;
}

CrouchAnimation::CrouchAnimation(){}

CrouchAnimation::CrouchAnimation(int frames, int index, SDL_Texture* m_texture, RenderManager* rm, ImageLibrary& imageLibrary)
{
	m_frames = frames;
	m_index = index;
	m_sprite.m_surface = imageLibrary.surfaces[m_index];
	m_sprite.m_texture = m_texture;
	m_sprite.SetSource(0, 0, imageLibrary.surfaces[m_index]->w / m_frames, imageLibrary.surfaces[m_index]->h);
	m_sprite.SetDestination(200, 700 - 16, m_sprite.m_source.w, m_sprite.m_source.h);
}

bool CrouchAnimation::Update(Uint32 dt, SceneManager& sceneManager, ImageLibrary& imageLibrary, MetaManager* m_mM)
{
	m_sprite.m_source.x = m_sprite.m_source.w * ((dt / 100) % m_frames);
	return true;
}

DieAnimation::DieAnimation(){}

DieAnimation::DieAnimation(int frames, int index, SDL_Texture* m_texture, RenderManager* rm, ImageLibrary& imageLibrary)
{
	m_frames = frames;
	m_index = index;
	m_sprite.m_surface = imageLibrary.surfaces[m_index];
	m_sprite.m_texture = m_texture;
	m_sprite.SetSource(0, 0, imageLibrary.surfaces[m_index]->w / m_frames, imageLibrary.surfaces[m_index]->h);
	m_sprite.SetDestination(200, 700 - 16, m_sprite.m_source.w, m_sprite.m_source.h);
}

bool DieAnimation::Update(Uint32 dt, SceneManager& sceneManager, ImageLibrary& imageLibrary, MetaManager* m_mM)
{
	m_mM->rM.Shake();
	m_sprite.m_source.x = m_sprite.m_source.w * ((dt / 100) % m_frames);
	clock++;
	if (clock == 6)
	{
		clock = 0;
		return false;
	}
	return true;
}