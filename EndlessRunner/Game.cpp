#include "Game.h"

Game::Game() : screen(this), managers(MetaManager()), worldGen(WorldGenerator(&managers.rM, &managers.cM)), lastScore(0)
{
	screen.Init();
	config.LoadOptions();
	managers.sdM.SetMusicVolume(50);
	managers.sdM.SetSoundVolume(50);
}

Game::~Game()
{
	printf("Destroy Game\n");
}

void Game::Init(ImageLibrary& imageLibrary)
{
	managers.sdM.LoadSettings(config);
	ratBastard = new Player(&managers, &screen, imageLibrary);

	managers.hM.PrintHighScore();

	managers.rM.Init(screen, &config);
	worldGen.Start(screen, ratBastard, imageLibrary);
}

bool Game::Run(Uint32 time, SceneManager& sceneManager, ImageLibrary& imageLibrary)
{
	managers.sdM.Update();
	SDL_SetRenderDrawColor(screen.renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(screen.renderer);
	SDL_SetRenderDrawColor(screen.renderer, 0xff, 0xff, 0xff, 0xff);
	return CheckStateToPlay(time, sceneManager, imageLibrary);
}

bool Game::CheckStateToPlay(Uint32 time, SceneManager& sceneManager, ImageLibrary& imageLibrary)
{
	switch (managers.gM.GetGameState())
	{
	case GameState::Game_MainMenu: break;
	case GameState::Game_Playing: UpdatePlaying(time, 0.016f, sceneManager, imageLibrary); break;
	case GameState::Game_HighScore: break;
	case GameState::Game_HighScoreInput: break;
	case GameState::Game_Options: break;
	case GameState::Game_Quit: 
		return false;
	default: break;
	}
	return true;
}
void Game::UpdatePlaying(Uint32 time, float dt, SceneManager& sceneManager, ImageLibrary& imageLibrary)
{
	if (managers.gM.m_choice == Choice::Choice_Pending)
	{
		worldGen.Reset();
		worldGen.Start(screen, ratBastard, imageLibrary);
		managers.gM.m_choice = Choice::Choice_None;
	}
	else
	{
		if (managers.gM.GetPlayState() != PlayState::Play_Death)
		{
			sceneManager.p_CurrentScreen->m_numbers[0].Add(1, imageLibrary);
			managers.hM.currentScore = sceneManager.p_CurrentScreen->m_numbers[0].m_value;
			worldGen.Update(dt, sceneManager, imageLibrary);
			ratBastard->Update(dt, time, sceneManager, imageLibrary);
		}
	}
}

void Game::Render(ImageLibrary& imageLibrary)
{
	if (managers.gM.GetGameState() == GameState::Game_Playing && managers.gM.GetPlayState() != PlayState::Play_Death)
	{
		worldGen.Render(imageLibrary);
		ratBastard->Render();
	}
	managers.rM.RenderHUD();
	SDL_RenderPresent(screen.renderer);
}

void Game::OnKeyDown(KeyCode key, SceneManager& sceneManager, ImageLibrary& imageLibrary)
{
	if (managers.gM.GetGameState() == GameState::Game_Playing)
	{
		switch (managers.gM.GetPlayState())
		{
		case PlayState::Play_Play:ratBastard->OnKeyDown(key); break;
		case PlayState::Play_Death: sceneManager.OnKeyDown(key, managers.rM, imageLibrary); break;
		}
	}
	else if (managers.gM.GetGameState() == GameState::Game_HighScoreInput)
	{
		sceneManager.m_input->OnInput(key);
		sceneManager.OnKeyDown(key, managers.rM, imageLibrary);
	}
	else
	{
		sceneManager.OnKeyDown(key, managers.rM, imageLibrary);
	}
	if (key == KeyCode::F1)
	{
		managers.gM.ChangeDebugState(DebugState::Debug_Off);
	}
	if (key == KeyCode::F2)
	{
		managers.gM.ChangeDebugState(DebugState::Debug_On);
	}
	if (key == KeyCode::F3)
	{
		managers.gM.ChangeDebugState(DebugState::Debug_AnimationTest);
	}
}

void Game::OnKeyUp(KeyCode key)
{
	switch (managers.gM.GetGameState())
	{
	case GameState::Game_MainMenu: break;
	case GameState::Game_Playing: ratBastard->OnKeyUp(key); break;
	case GameState::Game_HighScore: break;
	case GameState::Game_HighScoreInput: break;
	case GameState::Game_Options: break;
	default: break;
	}
}

void Game::QuitGame()
{
	managers.rM.OnQuit();
	managers.hM.SaveHighScore();
	managers.sdM.OnQuit();
	config.WriteOptions();
	managers.hM.PrintHighScore();
}