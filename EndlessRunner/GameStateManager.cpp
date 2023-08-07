#include "GameStateManager.h"

GameStateManager::GameStateManager() : m_State(GameState::Game_MainMenu), m_debugState(DebugState::Debug_Off), m_choice(Choice::Choice_None), m_playState(PlayState::Play_Play)
{

}
GameStateManager::~GameStateManager()
{

}
void GameStateManager::ChangeGameState(GameState newState)
{
	m_State = newState;
	if (m_State != GameState::Game_Playing)
	{
		ChangePlayState(PlayState::Play_Play);
	}
	m_choice = Choice::Choice_Pending;
}
GameState GameStateManager::GetGameState()
{
	return m_State;
}
void GameStateManager::ChangeDebugState(DebugState newState)
{
	m_debugState = newState;
}
DebugState GameStateManager::GetDebugState()
{
	return m_debugState;
}

void GameStateManager::ChangePlayState(PlayState newState)
{
	m_playState = newState;
}

PlayState GameStateManager::GetPlayState()
{
	return m_playState;
}

void GameStateManager::MakeChoice()
{
	m_choice = Choice::Choice_None;
}