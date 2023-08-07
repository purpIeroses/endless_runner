#ifndef SCREEN_H_DEFINED
#define SCREEN_H_DEFINED

#include "SDL.h"
#include "SDL_image.h"

class Game;

class Screen
{
	Game* game;
public:
	void Init();
	SDL_Renderer* renderer;
	SDL_Window* window;
	Screen(Game* game);
	~Screen();
};

#endif