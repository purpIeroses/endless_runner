#include "obstacle.h"

obstacle::obstacle()
{

}

obstacle::obstacle(RenderManager* in): trans(Vector2(0, 0))
{
	renderManager = in;
}

void obstacle::Start()
{
}

void obstacle::Update(float dt)
{
}

void obstacle::Render()
{
	//sprite.SetDestination(trans.m_position.m_x, trans.m_position.m_y, 16, 16);
	renderManager->Render(&sprite, trans);
}