#include "Animator.h"

Animator::Animator(){}

Animator::Animator(Screen* screen, RenderManager* rm, ImageLibrary& imageLibrary)
{
	animations.push_back(new WalkAnimation(4, 0, SDL_CreateTextureFromSurface(screen->renderer, imageLibrary.surfaces[0]), rm, imageLibrary));
	animations.push_back(new CrouchAnimation(3, 3, SDL_CreateTextureFromSurface(screen->renderer, imageLibrary.surfaces[3]), rm, imageLibrary));
	animations.push_back(new DieAnimation(3, 4, SDL_CreateTextureFromSurface(screen->renderer, imageLibrary.surfaces[4]), rm, imageLibrary));
}

Animator::~Animator()
{
	for (int i = 0; i < animations.size(); i++)
	{
		delete(animations[i]);
	}
}
