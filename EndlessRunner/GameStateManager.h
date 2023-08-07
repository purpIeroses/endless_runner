#ifndef GAMESTATEMANAGER_H_DEFINED
#define GAMESTATEMANAGER_H_DEFINED

enum class GameState
{
	Game_MainMenu = 0,
	Game_Playing = 1,
	Game_HighScore = 2,
	Game_HighScoreInput = 3,
	Game_Options = 4,
	Game_Quit = 5
};
enum class DebugState
{
	Debug_Off = 0,
	Debug_On = 1,
	Debug_AnimationTest = 2
};
enum class PlayState
{
	Play_Off = 0,
	Play_Play = 1,
	Play_Death = 2
};
enum class Choice
{
	Choice_None = 0,
	Choice_Pending = 1
};
struct GameStateManager
{
	GameState m_State;
	DebugState m_debugState;
	PlayState m_playState;
	Choice m_choice;

	GameStateManager();
	~GameStateManager();

	void ChangeGameState(GameState newState);
	GameState GetGameState();

	void ChangeDebugState(DebugState newState);
	DebugState GetDebugState();

	void ChangePlayState(PlayState newState);
	PlayState GetPlayState();

	void MakeChoice();
};
#endif