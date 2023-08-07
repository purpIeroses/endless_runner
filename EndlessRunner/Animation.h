#ifndef ANIMATION_H_DEFINED
#define ANIMATION_H_DEFINED

#include "SDL_image.h"
#include "RenderManager.h"
#include <string>
#include <array>
#include <random>
#include "ImageLibrary.h"
#include "SceneManager.h"
#include "ManagerManager.h"

struct Animation
{
	Sprite m_sprite;
	int m_frames;
	int m_index;
	int m_animationtype;
	Animation();
	Animation(int frames, int index, SDL_Texture* m_texture, RenderManager* rm, ImageLibrary& imageLibrary, int animationtype);
	virtual bool Update(Uint32 dt, SceneManager& sceneManager, ImageLibrary& imageLibrary, MetaManager* m_mM);
	Sprite GetSprite();
};

struct WalkAnimation: public Animation
{
	WalkAnimation();
	WalkAnimation(int frames, int index, SDL_Texture* m_texture, RenderManager* rm, ImageLibrary& imageLibrary);
	bool Update(Uint32 dt, SceneManager& sceneManager, ImageLibrary& imageLibrary, MetaManager* m_mM) override;
};

struct CrouchAnimation: public Animation
{
	CrouchAnimation();
	CrouchAnimation(int frames, int index, SDL_Texture* m_texture, RenderManager* rm, ImageLibrary& imageLibrary);
	bool Update(Uint32 dt, SceneManager& sceneManager, ImageLibrary& imageLibrary, MetaManager* m_mM) override;
};

struct DieAnimation: public Animation
{
	int clock = 0;
	DieAnimation();
	DieAnimation(int frames, int index, SDL_Texture* m_texture, RenderManager* rm, ImageLibrary& imageLibrary);
	bool Update(Uint32 dt, SceneManager& sceneManager, ImageLibrary& imageLibrary, MetaManager* m_mM) override;
};
#endif