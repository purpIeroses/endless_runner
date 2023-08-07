#include "WorldGenerator.h"

WorldGenerator::WorldGenerator(RenderManager* renM, CollisionManager* colM) : mNumber(0), startRand(0), speed(10), gap(false),
calledObst(false), obstGap(200.0f), obstIndex(1), ob1(obstacle(renM)), ob2(obstacle(renM)), ob0IsFirst(false), obsOnScreen(0), 
screen(nullptr), player(nullptr), background()
{
	renderManager = renM;
	collisionManager = colM;
	obs.push_back(&ob1);
	obs.push_back(&ob2);
}

void WorldGenerator::Start(Screen& givenScreen, Player* pl, ImageLibrary& imageLibrary)
{
	background = Background(renderManager, imageLibrary);
	player = pl;
	screen = &givenScreen;
	srand(rd());
	startRand = rand() % 127 + 128;
	mNumber = 0;
	myRand();
	makeObstacle(0, imageLibrary);
	ob0IsFirst = true;
}
void WorldGenerator::Update(float dt, SceneManager& sceneManager, ImageLibrary& imageLibrary)
{
	if (ob0IsFirst || obsOnScreen == 2)
	{
		obs[0]->trans.m_position.x -= speed;
		if (obs[0]->trans.m_position.x < -obs[0]->col.rect.w)
		{
			ob0IsFirst = false;
			obsOnScreen--;
			calledObst = false;
		}
	}

	if (obsOnScreen == 2 || (!ob0IsFirst && obsOnScreen == 1))
	{
		obs[1]->trans.m_position.x -= speed;
		if (obs[1]->trans.m_position.x < -obs[1]->col.rect.w)
		{
			ob0IsFirst = true;
			obsOnScreen--;
			calledObst = false;
		}
	}

	if (obsOnScreen == 0)
	{
		makeObstacle(0, imageLibrary);
		ob0IsFirst = true;
	}

	if (ob0IsFirst && obs[0]->trans.m_position.x <= obstGap && obs[0]->trans.m_position.x >= obstGap - 2 * speed)
	{
		if (obsOnScreen == 1 && !calledObst)
		{
			makeObstacle(1, imageLibrary);
			calledObst = true;
		}
	}
	else if (obs[1]->trans.m_position.x <= obstGap && obs[1]->trans.m_position.x >= obstGap - 2 * speed)
	{
		if (obsOnScreen == 1 && !calledObst)
		{
			if (makeObstacle(0, imageLibrary))
			{
				ob0IsFirst = true;
				calledObst = true;
			}
		} 
	}
	obs[0]->col.SetPosition((int)obs[0]->trans.m_position.x, (int)obs[0]->trans.m_position.y);
	obs[1]->col.SetPosition((int)obs[1]->trans.m_position.x, (int)obs[1]->trans.m_position.y);

	obs[0]->sprite.m_destination.x = (int)obs[0]->trans.m_position.x;
	obs[1]->sprite.m_destination.x = (int)obs[1]->trans.m_position.x;
	
	for(obstacle* o : obs)
	{
		if (collisionManager->AABB(o->col, player->m_collider))
		{
			player->Die();
		}
	}
	background.Update();
}

bool WorldGenerator::makeObstacle(const int ob, ImageLibrary& imageLibrary)
{
	if (myRand() % 256 < 64 || obsOnScreen == 0 || obstIndex == 1) // obstacle?
	{
		int tempRand = myRand() % 256;
		if (tempRand < 86) // lolipop (bird)
		{
			obs[ob]->col.rect.w = 1 * 16;
			obs[ob]->col.rect.h = 1 * 16;
			obs[ob]->trans.SetPosition(800, 700 - (obs[ob]->col.rect.h * 1.5f));
			obs[ob]->sprite.m_surface = imageLibrary.surfaces[2];
			obs[ob]->sprite.SetDestination((int)obs[ob]->trans.m_position.x, (int)obs[ob]->trans.m_position.y, 16, 32);
			obs[ob]->sprite.m_texture = SDL_CreateTextureFromSurface(screen->renderer, imageLibrary.surfaces[2]);
			obs[ob]->sprite.SetSource(0, 0, 16, 32);
		}
		else // ground obst (cactus)
		{
			obs[ob]->col.rect.w = (myRand() % 3 + 1) * 16;
			obs[ob]->col.rect.h = (myRand() % 2 + 1) * 16;
			obs[ob]->trans.SetPosition(800, 700 - (float)obs[ob]->col.rect.h);
			obs[ob]->sprite.m_surface = imageLibrary.surfaces[1];
			obs[ob]->sprite.m_texture = SDL_CreateTextureFromSurface(screen->renderer, imageLibrary.surfaces[1]);
			obs[ob]->sprite.SetSource(0, 0, 16, 16);
		}
		obsOnScreen++;
		return true;
	}
	return false;
}

uint32_t WorldGenerator::myRand()
{
	mNumber = obstIndex * startRand;
	obstIndex++;
	mNumber += 0xe120fc15;
	uint64_t tmp;
	tmp = (uint64_t)mNumber * 0x4a39b70d;
	uint32_t m1 = (tmp >> 32) ^ tmp;
	tmp = (uint64_t)m1 * 0x12fad5c9;
	uint32_t m2 = (tmp >> 32) ^ tmp;
	return m2;
}

void WorldGenerator::Render(ImageLibrary& imageLibrary)
{
	background.Render();
	for (int o = 0; o < 2; o++)
	{
		if (obs[o]->sprite.m_surface == imageLibrary.surfaces[1])
		{
			Vector2 temp = { obs[o]->trans.m_position.x, obs[o]->trans.m_position.y };
			for (int i = 1; i <= obs[o]->col.rect.w / 16; i++)
			{
				for (int j = 1; j <= obs[o]->col.rect.h / 16; j++)
				{
					obs[o]->trans.SetPosition(temp.x + obs[o]->sprite.m_source.w * (i - 1), temp.y + obs[o]->sprite.m_source.h * (j - 1));
					obs[o]->Render();
				}
			}
			obs[o]->trans.SetPosition(temp.x, temp.y);
		}
		else if (obs[o]->sprite.m_surface == imageLibrary.surfaces[2])
		{
			obs[o]->Render();
		}
	}
}

void WorldGenerator::Reset()
{
	gap = false;
	calledObst = false;
	obstIndex = 1;
	obsOnScreen = 0;
	ob1 = obstacle(renderManager);
	ob2 = obstacle(renderManager);
}