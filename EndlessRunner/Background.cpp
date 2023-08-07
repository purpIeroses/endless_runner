#include "Background.h"

Background::Background(): speedK(0.5f)
{
}

Background::Background(RenderManager* renderManager, ImageLibrary& imageLibrary): speedK(0.5f)
{
	elements.push_back(new BackgroundElement(renderManager, *imageLibrary.sprites[2]));
	elements.push_back(new BackgroundElement(renderManager, *imageLibrary.sprites[3]));
	elements.push_back(new BackgroundElement(renderManager, *imageLibrary.sprites[4]));
	elements.push_back(new BackgroundElement(renderManager, *imageLibrary.sprites[5]));
	elements.push_back(new BackgroundElement(renderManager, *imageLibrary.sprites[6]));
	for (int i = 0; i < elements.size(); i++)
	{
		elements[i]->trans.m_position.y = - 17.0f;
	}
	ground = new BackgroundElement(renderManager, *imageLibrary.sprites[10]);
	ground->trans.SetPosition(0, 700/4);
}

Background::~Background()
{
}

void Background::Render()
{
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		Vector2 temp = { (float)elements[i]->trans.m_position.x, (float)elements[i]->trans.m_position.y };

		elements[i]->trans.SetPosition(temp.x + elements[i]->sprite.m_source.w* 1.5f, temp.y);
				elements[i]->Render();
		elements[i]->trans.SetPosition(temp.x, temp.y);
		elements[i]->Render();
	}

	{
		Vector2 temp = { (float)ground->trans.m_position.x, (float)ground->trans.m_position.y };
			ground->trans.SetPosition(temp.x + ground->sprite.m_source.w , temp.y);
			ground->Render();
			ground->trans.m_position = temp;
			ground->Render();
	}
}

void Background::Update()
{
	for(int i = 0; i < elements.size(); i++)
	{
		elements[i]->MoveAtSpeed(i * speedK);
	}
	ground->MoveAtSpeed(5);
}
