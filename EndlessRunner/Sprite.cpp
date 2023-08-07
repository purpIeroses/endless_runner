#include "Sprite.h"

Sprite::Sprite():m_source()
{

}
void Sprite::Destroy()
{
	m_texture = nullptr;
	m_surface = nullptr;
}
Sprite::~Sprite()
{
}
void Sprite::SetSource(int x, int y, int w, int h)
{
	m_source.x = x; m_source.y = y; m_source.w = w; m_source.h = h;
}
void Sprite::SetDestination(int x, int y, int w, int h)
{
	m_destination.x = x; m_destination.y = y; m_destination.w = w; m_destination.h = h;
}