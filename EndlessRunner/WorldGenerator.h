#ifndef WORLDGENERATOR_H_DEFINED
#define WORLDGENERATOR_H_DEFINED

#include <stdint.h>
#include <random>
#include "obstacle.h"
#include "Animation.h"
#include "Screen.h"
#include "Player.h"
#include "SceneManager.h"
#include "Background.h"

struct WorldGenerator
{
public:
	Screen* screen;
	WorldGenerator(RenderManager* renM, CollisionManager* colM);
	void Start(Screen& screen, Player* pl, ImageLibrary& imageLibrary);
	void Update(float dt, SceneManager& sceneManager, ImageLibrary& imageLibrary);
	bool makeObstacle(int ob, ImageLibrary& imageLibrary);
	void Render(ImageLibrary& imageLibrary);
	void Reset();
	uint32_t myRand();
	uint32_t mNumber;
	std::random_device rd;
	unsigned int startRand;
	const unsigned int speed;
	obstacle ob1;
	obstacle ob2;
	std::vector<obstacle*> obs;
	bool gap;
	bool calledObst;
	bool ob0IsFirst;
	const float obstGap;
	int obstIndex;
	int obsOnScreen;
	RenderManager* renderManager;
	CollisionManager* collisionManager;
	Player* player;
	Background background;
};

#endif