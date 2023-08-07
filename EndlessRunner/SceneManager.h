#ifndef SCREENMANAGER_H_DEFINED
#define SCREENMANAGER_H_DEFINED

#include <list>
#include <vector>
#include "Transform.h"
#include "GameStateManager.h"
#include "Grapheme.h"
#include "Sprite.h"
#include "Keycode.h"
#include "GUIObject.h"
#include "GUIButton.h"
#include "GUISlider.h"
#include "Scene.h"
#include "SoundManager.h"
#include "HighScoreInput.h"
#include "Highscore.h"

enum HUDAnchor
{
	TopLeftCorner = 0,
	Top = 1,
	TopRightCorner = 2,
	Left = 3,
	Center = 4,
	Right = 5,
	BottomLeftCorner = 6,
	Bottom = 7,
	BottomRightCorner = 8
};

struct SceneManager
{
	Highscore* m_score;
	HighScoreInput* m_input;

	Scene m_MainMenu;
	Scene m_NameInputScreen;
	Scene m_DeathScreen;
	Scene m_PlayingScreen;
	Scene m_HighScoreScreen;
	Scene m_OptionsScreen;

	Scene* p_CurrentScreen;

	SceneManager(RenderManager& rM, GameStateManager& gSM, SoundManager& sDM,ImageLibrary& imageLibrary, Highscore& highScore);

	void Update(RenderManager& renderManager, GameStateManager& gameStateManager, SoundManager& soundManager, ImageLibrary& imageLibrary);
	void ChangeScreen(GameStateManager& gM, RenderManager& rM, SoundManager& sM, ImageLibrary& imageLibrary);
	void OnKeyDown(KeyCode key, RenderManager& renderManager, ImageLibrary& imageLibrary);
	void OnQuitGame();
};
#endif