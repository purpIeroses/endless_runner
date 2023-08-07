#include "SceneManager.h"

SceneManager::SceneManager(RenderManager& rM, GameStateManager& gSM, SoundManager& sDM, ImageLibrary& imageLibrary, Highscore& highscore):
	p_CurrentScreen(nullptr),
	m_MainMenu(Scene(&std::vector<GUIObject*>
{
	new GUIButton(Transform(Vector2(0, 100)), Transform(Vector2(0, 100)), Transform(Vector2(125, 100)), 
		GameState::Game_Playing, imageLibrary.sprites[1], 
		Word("PLAY", imageLibrary),
		&gSM, imageLibrary),
	new GUIButton(Transform(Vector2(0, 150)), Transform(Vector2(0, 150)), Transform(Vector2(125, 150)), 
		GameState::Game_HighScore, imageLibrary.sprites[1], 
		Word("HIGHSCORES", imageLibrary),
		&gSM, imageLibrary),
	new GUIButton(Transform(Vector2(0, 200)), Transform(Vector2(0, 200)), Transform(Vector2(125, 200)), 
		GameState::Game_Options, imageLibrary.sprites[1], 
		Word("OPTIONS", imageLibrary),
		&gSM, imageLibrary),
	new GUIButton(Transform(Vector2(0, 250)), Transform(Vector2(0, 250)), Transform(Vector2(125, 250)),
		GameState::Game_Quit, imageLibrary.sprites[1],
		Word("QUIT", imageLibrary),
		&gSM, imageLibrary)
}, imageLibrary)),
	m_DeathScreen(Scene(&std::vector<GUIObject*>{
	new GUIButton(Transform(Vector2(0, 150)), Transform(Vector2(0, 150)), Transform(Vector2(125, 125)), 
		GameState::Game_HighScoreInput, imageLibrary.sprites[1], 
		Word("ENTER", imageLibrary), 
		&gSM, imageLibrary),
	new GUIButton(Transform(Vector2(0, 200)), Transform(Vector2(0, 200)), Transform(Vector2(125, 150)), 
		GameState::Game_MainMenu, imageLibrary.sprites[1], 
		Word("MENU", imageLibrary),
		&gSM, imageLibrary)
}, imageLibrary)),
	m_HighScoreScreen(Scene(&std::vector<GUIObject*>{
	new GUIButton(Transform(Vector2(0, 300)), Transform(Vector2(0, 300)), Transform(Vector2(125, 300)), 
		GameState::Game_MainMenu, imageLibrary.sprites[1], 
		Word("MENU", imageLibrary), 
		&gSM, imageLibrary),
}, & std::vector<Number>{
			Number(highscore.score5,100, 204, 1, 10, imageLibrary),
			Number(highscore.score4,100, 184, 1, 10, imageLibrary),
			Number(highscore.score3,100, 164, 1, 10, imageLibrary),
			Number(highscore.score2,100, 144, 1, 10, imageLibrary),
			Number(highscore.score1,100, 124, 1, 10, imageLibrary),
	},
& std::vector<Word>{
			Word(highscore.name5, 20, 204, imageLibrary), 
			Word(highscore.name4, 20, 184, imageLibrary), 
			Word(highscore.name3, 20, 164, imageLibrary),
			Word(highscore.name2, 20, 144, imageLibrary),
			Word(highscore.name1, 20, 124, imageLibrary)
	},
imageLibrary)),
	m_NameInputScreen(Scene(&std::vector<GUIObject*>{
	new GUIButton(Transform(Vector2(0, 200)), Transform(Vector2(0, 200)), Transform(Vector2(125, 275)), 
		GameState::Game_HighScore, imageLibrary.sprites[1], 
		Word("ENTER", imageLibrary), 
		&gSM, imageLibrary),
	new GUIButton(Transform(Vector2(0, 300)), Transform(Vector2(0, 300)), Transform(Vector2(125, 300)), 
		GameState::Game_MainMenu, imageLibrary.sprites[1], 
		Word("MENU", imageLibrary), 
		&gSM, imageLibrary)
}, imageLibrary)),
	m_OptionsScreen(Scene(&std::vector<GUIObject*>{
			new GUISlider(Transform(Vector2(175, 160)), Transform(Vector2(175, 160)), imageLibrary.sprites[9], imageLibrary.sprites[8], &gSM,
				sDM.music_volume, 128, 0, Number(100, 164, 1, 3, imageLibrary), imageLibrary),
			new GUISlider(Transform(Vector2(175, 180)), Transform(Vector2(175, 180)), imageLibrary.sprites[9], imageLibrary.sprites[8], &gSM,
				rM.HUDRenderDimensions, 3, 1, Number(100, 184, 1, 1, imageLibrary), imageLibrary),
			new GUISlider(Transform(Vector2(175, 200)), Transform(Vector2(175, 200)), imageLibrary.sprites[9], imageLibrary.sprites[8], &gSM,
				rM.RenderDimensions, 3, 1, Number(100, 204, 1, 1, imageLibrary), imageLibrary),
				new GUIButton(Transform(Vector2(0, 300)), Transform(Vector2(0, 300)), Transform(Vector2(175, 300)),
					GameState::Game_MainMenu, imageLibrary.sprites[1],
					Word("SAVE", imageLibrary),
					&gSM, imageLibrary)}
	, &std::vector<Number>{},
&std::vector<Word>{Word("RENDERSIZE", 20, 204, imageLibrary), Word("HUDRENDERSIZE", 20, 184, imageLibrary), Word("MUSICVOLUME", 20, 164, imageLibrary)},
imageLibrary)),
	m_PlayingScreen(Scene(&std::vector<Number>{ Number(0, 2 * 16, 1, 10, imageLibrary) }, imageLibrary))
{
	m_input = new HighScoreInput(&highscore, &gSM, imageLibrary);
	m_score = &highscore;
}
void SceneManager::OnQuitGame()
{
}

void SceneManager::Update(RenderManager& renderManager, GameStateManager& gameStateManager, SoundManager& soundManager, ImageLibrary& imageLibrary)
{
	if (gameStateManager.GetGameState() == GameState::Game_HighScoreInput)
	{
		m_input->Render(renderManager);
	}
	if (p_CurrentScreen->Update(imageLibrary))
	{
		ChangeScreen(gameStateManager, renderManager, soundManager, imageLibrary);
	}
}
void SceneManager::ChangeScreen(GameStateManager& gM, RenderManager& rM, SoundManager& sM, ImageLibrary& imageLibrary)
{
 	rM.EmptyHUDRenderObjects();
	switch (gM.GetGameState())
	{
	case GameState::Game_MainMenu: p_CurrentScreen = &m_MainMenu;
		sM.PlayMusic(sM.lib.getSong(1));
		break;
	case GameState::Game_HighScore: p_CurrentScreen = &m_HighScoreScreen;
		for (int i = 0; i < p_CurrentScreen->m_numbers.size(); i++)
		{
			p_CurrentScreen->m_numbers[i].Reset(imageLibrary);
		}
		p_CurrentScreen->m_numbers[0].Add(m_score->score5, imageLibrary);
		p_CurrentScreen->m_numbers[1].Add(m_score->score4, imageLibrary);
		p_CurrentScreen->m_numbers[2].Add(m_score->score3, imageLibrary);
		p_CurrentScreen->m_numbers[3].Add(m_score->score2, imageLibrary);
		p_CurrentScreen->m_numbers[4].Add(m_score->score1, imageLibrary);
		for (int i = 0; i < p_CurrentScreen->m_words.size(); i++)
		{
			p_CurrentScreen->m_words[i].Reset();
		}
		p_CurrentScreen->m_words.push_back(Word(m_score->name5, 20, 204, imageLibrary));
		p_CurrentScreen->m_words.push_back(Word(m_score->name4, 20, 184, imageLibrary));
		p_CurrentScreen->m_words.push_back(Word(m_score->name3, 20, 164, imageLibrary));
		p_CurrentScreen->m_words.push_back(Word(m_score->name2, 20, 144, imageLibrary));
		p_CurrentScreen->m_words.push_back(Word(m_score->name1, 20, 124, imageLibrary));
		break;
	case GameState::Game_HighScoreInput: p_CurrentScreen = &m_NameInputScreen;
		m_input->nameLength = 0;
		break;
	case GameState::Game_Options: p_CurrentScreen = &m_OptionsScreen;
		break;
	case GameState::Game_Playing:
		switch (gM.GetPlayState())
		{
		case PlayState::Play_Off: break;
		case PlayState::Play_Play: p_CurrentScreen = &m_PlayingScreen; 
			sM.PlayMusic(sM.lib.getSong(0));
			break;
		case PlayState::Play_Death: 
			p_CurrentScreen->m_numbers[0].Reset(imageLibrary);
			p_CurrentScreen = &m_DeathScreen; break;
		}
		break;
	default: break;
	}
	p_CurrentScreen->m_state = GUIObjectState::GOING_IN;
	p_CurrentScreen->Render(rM);
}

void SceneManager::OnKeyDown(KeyCode key, RenderManager& renderManager, ImageLibrary& imageLibrary)
{
	p_CurrentScreen->OnKeyDown(key, renderManager, imageLibrary);
}