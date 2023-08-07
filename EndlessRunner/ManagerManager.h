#ifndef MANAGERMANAGER_H_DEFINED
#define MANAGERMANAGER_H_DEFINED

#include "SDL_render.h"
#include "GameStateManager.h"
#include "CollisionManager.h"
#include "RenderManager.h"
#include "Highscore.h"
#include "ParticleManager.h"
#include "SoundManager.h"

struct MetaManager
{
	GameStateManager gM;
	CollisionManager cM;
	RenderManager rM;
	Highscore hM;
	ParticleManager pM;
	SoundManager sdM;
	MetaManager();
	~MetaManager();
};

#endif