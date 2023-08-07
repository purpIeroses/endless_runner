#include "Screen.h"
#include "Game.h"

void Screen::Init()
{
	/*window = SDL_CreateWindow("Endless Runner",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800,
		800,
		SDL_WINDOW_ALLOW_HIGHDPI);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);*/


}

Screen::Screen(Game* game)
{
	this->game = game;
	//window = NULL;

	window = SDL_CreateWindow("Endless Runner",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800,
		800,
		SDL_WINDOW_ALLOW_HIGHDPI);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Screen::~Screen()
{
	printf("Destroy Screen\n");
	SDL_DestroyWindow(window);
}
