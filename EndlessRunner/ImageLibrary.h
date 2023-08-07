#ifndef IMAGELIBRARY_H_DEFINED
#define IMAGELIBRARY_H_DEFINED

#include "SDL_surface.h"
#include "Sprite.h"
#include "Screen.h"
#include <vector>
struct ImageLibrary
{
	std::vector<SDL_Surface*> surfaces;
	std::vector<Sprite*> sprites;
	Sprite digitSprites[10];
	std::vector<Sprite> letterSprites;
	SDL_Surface* letters;
	SDL_Surface* numbers;
	bool Initialize(Screen* screen);
	void FreeSurfaces();
	void PushSprite(SDL_Surface* surface, Screen* screen);
	void DeleteSprites();
};

#endif