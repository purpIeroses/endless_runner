#include "ManagerManager.h"

MetaManager::MetaManager() :
	gM(GameStateManager()),
	rM(RenderManager()),
	cM(CollisionManager()),
	hM(Highscore()),
	pM(ParticleManager()),
	sdM(SoundManager())
{
}
MetaManager::~MetaManager()
{

}