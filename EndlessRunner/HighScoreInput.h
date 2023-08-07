#ifndef HIGHSCOREINPUT_H_DEFINED
#define HIGHSCOREINPUT_H_DEFINED

#include "Grapheme.h"
#include "Keycode.h"
#include "GameStateManager.h"
#include "Highscore.h"

struct HighScoreInput
{
	Highscore* m_highScore;
	GameStateManager* m_gameState;

	Letter letters[10];
	Sprite underline; Transform underline_trans;
	int nameLength;
	char name[10];
	HighScoreInput(Highscore* highScore, GameStateManager* gameState, ImageLibrary& imageLibrary);
	void InputLetter(char c);
	void EraseLetter();
	void EnterName();
	void OnInput(KeyCode key);
	void Render(RenderManager& renderManager);
};

#endif