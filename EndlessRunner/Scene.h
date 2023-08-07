#ifndef SCENE_H_DEFINED
#define SCENE_H_DEFINED

#include <vector>
#include "GUIObject.h"
#include "Grapheme.h"
#include "GUIArrow.h"

struct Scene
{
	GUIObjectState m_state;
	int index;
	bool m_transitioning;
	Scene();
	Scene(std::vector<GUIObject*>* objects, ImageLibrary& imageLibrary);
	Scene(std::vector<Number>* numbers, ImageLibrary& imageLibrary);
	Scene(std::vector<GUIObject*>* buttons, std::vector<Number>* numbers, ImageLibrary& imageLibrary);
	Scene(std::vector<GUIObject*>* buttons, std::vector<Number>* numbers, std::vector<Word>* words, ImageLibrary& imageLibrary);
	~Scene();
	bool Update(ImageLibrary& imageLibrary);
	GUIArrow* m_arrow;
	std::vector<GUIObject*> m_objects;
	std::vector<Number> m_numbers;
	std::vector<Word> m_words;
	//std::vector<Word> words;
	Sprite m_background;
	void Render(RenderManager& rM);
	void OnKeyDown(KeyCode key, RenderManager& renderManager, ImageLibrary& imageLibrary);
};
#endif