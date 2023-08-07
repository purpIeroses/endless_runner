#include "BackgroundElement.h"

BackgroundElement::BackgroundElement(RenderManager* in, Sprite sprt)
{
	renderManager = in;
	sprite = sprt;
	trans.SetPosition(0, 0);
}

void BackgroundElement::MoveAtSpeed(float speed)
{
	trans.m_position.x -= speed;
	if (trans.m_position.x <= -sprite.m_source.w*1.5f) { trans.m_position.x = 0; }
}

void BackgroundElement::Render()
{
	renderManager->RenderBackground(&sprite, trans);
}
