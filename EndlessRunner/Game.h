#ifndef GAME_H_DEFINED
#define GAME_H_DEFINED

#include "Screen.h"
#include "ManagerManager.h"
#include "SceneManager.h"
#include "WorldGenerator.h"
#include "Keycode.h"
#include "Player.h"
#include "Animator.h"
#include "SDL.h"
#include "Animation.h"
#include "Screen.h"

#include "Config.h"

class Game
{
	WorldGenerator worldGen;
	Player* ratBastard;
	Animator animator;

	Config config;

	int lastScore;
public:
	Screen screen;
	MetaManager managers;
	void Init(ImageLibrary& imageLibrary);
	bool Run(Uint32 time, SceneManager& sceneManager, ImageLibrary& imageLibrary);
	void Render(ImageLibrary& imageLibrary);
	Game();
	~Game();
	bool CheckStateToPlay(Uint32 time, SceneManager& sceneManager, ImageLibrary& imageLibrary);
	void UpdatePlaying(Uint32 time, float dt, SceneManager& sceneManager, ImageLibrary& imageLibrary);

	void QuitGame();

	void OnKeyDown(KeyCode key, SceneManager& sceneManager, ImageLibrary& imageLibrary);
	void OnKeyUp(KeyCode key);
};

#endif