#ifndef ANIMATOR_H_DEFINED
#define ANIMATOR_H_DEFINED

#include <vector>
#include "Screen.h"
#include "RenderManager.h"
#include "Animation.h"
#include "ImageLibrary.h"

struct Animator
{
	bool m_locked;
	Animator();
	Animator(Screen* screen, RenderManager* rm, ImageLibrary& imagelibrary);
	~Animator();
	std::vector<Animation*> animations;
};

#endif