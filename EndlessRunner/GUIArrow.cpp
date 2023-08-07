#include "GUIArrow.h"

GUIArrow::GUIArrow(Transform& trans, ImageLibrary& imageLibrary)
{
	m_trans.SetPosition(trans.m_position.x + 0, trans.m_position.y);
	m_sprite = *imageLibrary.sprites[7];
	m_sprite.SetSource(0, 0, 0, 0);
	currentObject = nullptr;
	m_active = false;
}
void GUIArrow::Move()
{
	if (currentObject)
	{
		m_trans.SetPosition(currentObject->GetArrowX(), currentObject->m_position.m_position.y);
	}
}
void GUIArrow::Render(RenderManager& rM)
{
	rM.AddToHUDRenderObjects(&m_sprite, &m_trans);
}

void GUIArrow::ToggleArrow()
{
	if (m_sprite.m_source.w != 0)
	{
		m_sprite.SetSource(m_sprite.m_source.x, m_sprite.m_source.y, 0, 0);
		m_active = false;
	}
	else
	{
		m_sprite.SetSource(m_sprite.m_source.x, m_sprite.m_source.y, 16, 16);
		m_active = true;
	}
}