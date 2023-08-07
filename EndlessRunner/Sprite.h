#ifndef SPRITE_H_DEFINED
#define SPRITE_H_DEFINED

#include "SDL_image.h"

struct Sprite
{
	SDL_Surface* m_surface;
	SDL_Texture* m_texture;
	SDL_Rect m_source;
	SDL_Rect m_destination;
	Sprite();
	~Sprite();

	void Destroy();
	void SetSource(int x, int y, int w, int h);
	void SetDestination(int x, int y, int w, int h);
};
#endif