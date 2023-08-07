#include "HighScoreInput.h"

HighScoreInput::HighScoreInput(Highscore* highScore, GameStateManager* gameState, ImageLibrary& imageLibrary)
{
	m_highScore = highScore;
	m_gameState = gameState;
	underline = *imageLibrary.sprites[11];
	underline_trans.SetPosition(40, 80);

	//if (underline.image == nullptr)
	//{
	//	underline.SetImage(ImageLibrary::text); underline.SetSource(0, 7 * 8, 10 * 8, 8);
	//	underline_trans.SetPosition(16 * 5.5, 16 * 17.5f); underline_trans.SetScale(4, 4);
	//}
	letters[0] = Letter('a', 40, 65, imageLibrary); letters[0].m_trans.SetScale(4, 4);
	nameLength = 0;
	for (int i = 1; i < 10; i++)
	{
		letters[i] = Letter('a', (int)letters[0].m_trans.m_position.x + (i * 3) * (int)letters[0].m_trans.m_scale.x, (int)letters[0].m_trans.m_position.y, imageLibrary);
		letters[i].m_trans.SetScale(1, 1);
	}
}
void HighScoreInput::InputLetter(char c)
{
	if (nameLength != 10)
	{
		name[nameLength] = c;
		letters[nameLength].m_value = c; letters[nameLength].Update();
		nameLength++;
	}
}
void HighScoreInput::EraseLetter()
{
	if (nameLength != 0)
	{
		nameLength--;
	}
}
void HighScoreInput::EnterName()
{
	std::string nameToEnter;
	for (int i = 0; i < nameLength; i++)
	{
		nameToEnter.push_back(name[i]);
	}
	m_highScore->UpdateHighScore(m_highScore->currentScore, nameToEnter);
	m_gameState->m_choice = Choice::Choice_None;
	m_gameState->ChangeGameState(GameState::Game_HighScore);
}
void HighScoreInput::OnInput(KeyCode key)
{
	switch (key)
	{
	case KeyCode::A: InputLetter('A'); break;
	case KeyCode::B: InputLetter('B'); break;
	case KeyCode::C: InputLetter('C'); break;
	case KeyCode::D: InputLetter('D'); break;
	case KeyCode::E: InputLetter('E'); break;
	case KeyCode::F: InputLetter('F'); break;
	case KeyCode::G: InputLetter('G'); break;
	case KeyCode::H: InputLetter('H'); break;
	case KeyCode::I: InputLetter('I'); break;
	case KeyCode::J: InputLetter('J'); break;
	case KeyCode::K: InputLetter('K'); break;
	case KeyCode::L: InputLetter('L'); break;
	case KeyCode::M: InputLetter('M'); break;
	case KeyCode::N: InputLetter('N'); break;
	case KeyCode::O: InputLetter('O'); break;
	case KeyCode::P: InputLetter('P'); break;
	case KeyCode::Q: InputLetter('Q'); break;
	case KeyCode::R: InputLetter('R'); break;
	case KeyCode::S: InputLetter('S'); break;
	case KeyCode::T: InputLetter('T'); break;
	case KeyCode::U: InputLetter('U'); break;
	case KeyCode::V: InputLetter('V'); break;
	case KeyCode::W: InputLetter('W'); break;
	case KeyCode::X: InputLetter('X'); break;
	case KeyCode::Y: InputLetter('Y'); break;
	case KeyCode::Z: InputLetter('Z'); break;
	case KeyCode::SPACE: EnterName(); break;
	case KeyCode::ENTER: EnterName(); break;
	case KeyCode::BACKSPACE: EraseLetter(); break;
	default: return;
	}
}
void HighScoreInput::Render(RenderManager& renderManager)
{
	for (int i = 0; i < nameLength; i++)
	{
		renderManager.RenderBackground(&letters[i].m_sprite, letters[i].m_trans);
	}
	renderManager.RenderBackground(&underline, underline_trans);
	//renderManager.RenderHUD(yourName, yourName_trans);
}
