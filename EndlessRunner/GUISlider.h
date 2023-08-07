#ifndef GUISLIDER_H_DEFINED
#define GUISLIDER_H_DEFINED

#include "GUIButton.h"
#include "Keycode.h"

struct GUISlider:GUIObject
{
	Sprite m_leverSprite;
	Transform m_leverTrans;
	Number m_number;
	float m_maxValue;
	float m_minValue;
	float* m_currentValue;
	GUISlider();
	GUISlider(Transform leverTrans, Transform trans, Sprite* leverSprite, Sprite* sprite, GameStateManager* gM, float& value, float maxValue, float minValue, Number number, ImageLibrary& imageLibrary);
	bool OnKeyDown(KeyCode key, RenderManager& renderManager) override;
	void MoveSlider(int i);
	bool Update(ImageLibrary& imageLibrary) override;
	void Render(RenderManager& renderManager) override;
	void ToggleHighlight(bool value, ImageLibrary& imageLibrary) override;
};

#endif