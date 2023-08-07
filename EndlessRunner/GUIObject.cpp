#include "GUIObject.h"

GUIObject::GUIObject()
{

}
GUIObject::GUIObject(Transform pos, Transform off, Transform menu, Sprite* sprite, GameStateManager* gM) : m_position(pos), 
	m_offscreen(off), m_menuscreen(menu), m_sprite(*sprite), p_gM(gM), x(0), y(0), m_speed(0.7f)
{
	//m_trans.SetScale(2, 2);
}
void GUIObject::ToggleHighlight(bool value, ImageLibrary& imageLibrary)
{
	if (value == true)
	{
		m_sprite = *imageLibrary.sprites[0];
	}
	else
	{
		m_sprite = *imageLibrary.sprites[1];
	}
}
void GUIObject::SetState(GUIObjectState* state)
{
	p_state = state;
}
bool GUIObject::OnClick(RenderManager& renderManager)
{
	return false;
}
float GUIObject::GetArrowX()
{
	return m_position.m_position.x + m_sprite.m_source.w + 30.0f;
}
bool GUIObject::OnKeyDown(KeyCode key, RenderManager& renderManager)
{
	return false;
}
void GUIObject::Render(RenderManager& rM)
{
	rM.AddToHUDRenderObjects(&m_sprite, &m_position);
}

bool GUIObject::Update(ImageLibrary& imageLibrary)
{
	return false;
}

void GUIObject::Ease(Transform& from, Transform& to)
{
	const float a = 4.0f;
	const float b = 1.0f;
	const float c = -1.0f;
	const float d = 4.0f;
	if (from.m_position.x > to.m_position.x)
	{
		if (m_position.m_position.x > to.m_position.x)
		{
			m_clock += m_speed;
			if (m_position.m_position.x - m_clock <= to.m_position.x)
			{
				m_position.m_position.x = to.m_position.x;
			}
			else
			{
				m_position.m_position.x -= m_clock;
			} //a* atan(b * m_clock - c) + d;
		    //m_position.m_position.x = a * atan(b * m_clock - c) + d;
			if (m_position.m_position.x <= to.m_position.x)
			{
				m_clock = 0;
			}
		}
	}
	if (from.m_position.x < to.m_position.x)
	{
		if (m_position.m_position.x < to.m_position.x)
		{
			m_clock += m_speed;
			if (m_position.m_position.x + m_clock >= to.m_position.x)
			{
				m_position.m_position.x = to.m_position.x;
			}
			else
			{
				m_position.m_position.x += m_clock;
			}
			// a* atan(b * m_clock - c) + d;
			//m_position.m_position.x = a * atan(b * m_clock - c) + d;
			if (m_position.m_position.x >= to.m_position.x)
			{
				m_clock = 0;
			}
		}
	}
}
GUIObject::~GUIObject()
{

}