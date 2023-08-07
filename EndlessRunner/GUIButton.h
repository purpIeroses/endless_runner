#ifndef GUIBUTTON_H_DEFINED
#define GUIBUTTON_H_DEFINED

#include "GUIObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Grapheme.h"

struct GUIButton: public GUIObject
{
	bool isActivated;
	int vector_size;
	ImageLibrary imglib;
	GameState m_gameState;
	Word m_text;
	Sprite beginning;
	Sprite end;
	Sprite middle;
	Sprite selected_beginning;
	Sprite selected_end;
	Sprite selected_middle;
	std::vector<Sprite> middles;
	std::vector<Sprite> middles_copy;
	std::vector<Sprite> selected_middles;
	std::vector<Transform*> transforms;
	GUIButton();
	GUIButton(Transform pos, Transform off, Transform menu, GameState heldState, Sprite* sprite, GameStateManager* gM);
	GUIButton(Transform pos, Transform off, Transform menu, GameState heldState, Sprite* sprite, Word word, GameStateManager* gM, ImageLibrary& imageLibrary);
	~GUIButton() override;
	bool Update(ImageLibrary& imageLibrary) override;
	void ToggleHighlight(bool value, ImageLibrary& imageLibrary) override;
	bool OnClick(RenderManager& renderManager) override;
	bool OnKeyDown(KeyCode key, RenderManager& renderManager) override;
	void Render(RenderManager& rM) override;
	void MakeModular(int size);
	void MakeSelectedModular(int size);
	void MakePositions();
	virtual float GetArrowX() override;
};

#endif