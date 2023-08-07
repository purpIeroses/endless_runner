#ifndef BACKGROUND_H_DEFINED
#define BACKGROUND_H_DEFINED

#include "BackgroundElement.h"
#include <vector>
#include "RenderManager.h"
#include "ImageLibrary.h"
struct Background
{
	Background();
	Background(RenderManager* renderManager, ImageLibrary& imageLibrary);
	~Background();
	std::vector<BackgroundElement*> elements;
	BackgroundElement* ground;
	void Render();
	void Update();
	float speedK;
};
#endif