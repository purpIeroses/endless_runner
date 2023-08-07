#include "GUIButton.h"
GUIButton::GUIButton(): isActivated(false), m_gameState(GameState::Game_MainMenu)
{

}
GUIButton::GUIButton(Transform pos, Transform off, Transform menu, GameState state, Sprite* sprite, GameStateManager* gM) : m_gameState(state), GUIObject(pos, off, menu, sprite, gM)
{
	isActivated = false;
	m_position.m_position.x = (float)-sprite->m_surface->w;
	m_offscreen.m_position.x = (float)-sprite->m_surface->w;
	//m_trans.SetScale(2, 2);
}
GUIButton::GUIButton(Transform pos, Transform off, Transform menu, GameState state, Sprite* sprite, Word word, GameStateManager* gM, ImageLibrary& imageLibrary) : m_gameState(state), GUIObject(pos, off, menu, sprite, gM),
m_text(word)
{
	imglib = imageLibrary;
	isActivated = false;
	m_position.m_position.x = (float)-sprite->m_surface->w;
	m_offscreen.m_position.x = (float)-sprite->m_surface->w;
	beginning = *sprite;
	end = *sprite;
	middle = *sprite;
	beginning.SetSource(0, 0, 16, 16);
	middle.SetSource(16, 0, 16, 16);
	end.SetSource(32, 0, 16, 16);
	selected_beginning = *imglib.sprites[0];
	selected_end = *imglib.sprites[0];
	selected_middle = *imglib.sprites[0];
	selected_beginning.SetSource(0, 0, 16, 16);
	selected_middle.SetSource(16, 0, 16, 16);
	selected_end.SetSource(32, 0, 16, 16);
	vector_size = word.letters.size();
	MakeModular(vector_size);
	MakeSelectedModular(vector_size);
	MakePositions();
	//m_offscreen.m_position.y = 0 - (middles.size() * 16);
	m_menuscreen.m_position.x = 200 - (middles.size() * 16)*0.5f;
	m_offscreen.m_position.x = 0 - (middles.size() * 16)*0.5f;
	//m_position.m_position.x = 800 - (middles.size() * 16);
	//m_trans.SetScale(2, 2);
}

void GUIButton::MakeModular(int size)
{
	int finalsize = size - 2;
	for (int x = 0; x < finalsize; x++)
	{
		if (x % 2 == 0)
		{
			middles.push_back(middle);
		}
	}
	middles.insert(middles.begin(), beginning);
	middles.push_back(end);
	for (int x = 0; x < middles.size(); x++)
	{
		middles_copy.push_back(middles[x]);
	}
}

void GUIButton::MakeSelectedModular(int size)
{
	int finalsize = size - 2;
	for (int x = 0; x < finalsize; x++)
	{
		if (x % 2 == 0)
		{
			selected_middles.push_back(selected_middle);
		}
	}
	selected_middles.insert(selected_middles.begin(), selected_beginning);
	selected_middles.push_back(selected_end);
}

void GUIButton::MakePositions()
{
	for (unsigned int x = 0; x < middles.size(); x++)
	{
		Transform* trans = new Transform();
		trans->SetPosition((int)x * 16 - 48, m_position.m_position.y);
		transforms.push_back(trans);
	}
}

bool GUIButton::OnClick(RenderManager& renderManager)
{
	isActivated = true;
	*p_state = GUIObjectState::GOING_OUT;
	return true;
	//SoundManager::PlaySound(SoundLibrary::sound_Type, 0);
}
bool GUIButton::Update(ImageLibrary& imageLibrary)
{
	if (*p_state == GUIObjectState::GOING_IN)
	{
		Ease(m_offscreen, m_menuscreen);
	}
	else if (*p_state == GUIObjectState::GOING_OUT)
	{
		Ease(m_menuscreen, m_offscreen);
	}
	else if (isActivated)
	{
		p_gM->ChangeGameState(m_gameState);
		isActivated = false;
		return true;
	}
	if (m_text.letters.size()!=0)
	{
		m_text.Move(Vector2(m_position.m_position.x + 8, m_position.m_position.y + 4));
	}
	for (int i = 0; i < middles.size(); i++)
	{
		transforms[i]->SetPosition(m_position.m_position.x + i * 16, m_position.m_position.y);
	}
	return false;
}
bool GUIButton::OnKeyDown(KeyCode key, RenderManager& renderManager)
{
	switch (key)
	{
	case KeyCode::SPACE: OnClick(renderManager); return true;
	case KeyCode::ENTER: OnClick(renderManager); return true;
	}
	return false;
}
void GUIButton::Render(RenderManager& rM)
{
	for (unsigned int i = 0; i < middles.size(); i++)
	{
		rM.AddToHUDRenderObjects(&middles[i], transforms[i]);
	}
	m_text.Render(rM);
}
GUIButton::~GUIButton()
{
	m_sprite.Destroy();
}

void GUIButton::ToggleHighlight(bool value, ImageLibrary& imageLibrary)
{
	if (value == true)
	{
		for (unsigned int i = 0; i < middles.size(); i++)
		{
			middles[i] = selected_middles[i];
		}
	}
	else
	{
		for (unsigned int i = 0; i < middles.size(); i++)
		{
			middles[i] = middles_copy[i];
		}
	}
}

float GUIButton::GetArrowX()
{
	return transforms[transforms.size() - 1]->m_position.x + 30;
}