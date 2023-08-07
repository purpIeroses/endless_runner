#include "GUISlider.h"

GUISlider::GUISlider()
{

}
GUISlider::GUISlider(Transform leverTrans, Transform trans, Sprite* leverSprite, Sprite* sprite, GameStateManager* gM, float& value, float maxValue, float minValue, Number number, ImageLibrary& imageLibrary): m_leverTrans(leverTrans), m_leverSprite(*leverSprite),
GUIObject(trans, trans, trans, sprite, gM), m_number(number)
{
	m_maxValue = maxValue;
	m_currentValue = &value;
	m_minValue = minValue;
	m_number.Add(*m_currentValue, imageLibrary);
	m_leverTrans.m_position.x = (*m_currentValue -m_minValue) * ( (float)m_sprite.m_source.w / (m_maxValue - m_minValue)) + m_position.m_position.x - ((float)m_leverSprite.m_source.w * 0.5f);
}

bool GUISlider::OnKeyDown(KeyCode key, RenderManager& renderManager)
{
	switch (key)
	{
	case KeyCode::LEFT_ARROW: MoveSlider(-1); break;
	case KeyCode::RIGHT_ARROW: MoveSlider(1); break;
	}
	return false;
}
void GUISlider::MoveSlider(int i)
{
	float percentageUnit = ((m_sprite.m_source.w) / (m_maxValue - m_minValue));
	if (i == -1 && (m_leverTrans.m_position.x + (float)m_leverSprite.m_source.w * 0.5f) - percentageUnit >= (m_position.m_position.x))
	{
		m_leverTrans.m_position.x -= percentageUnit;
		(*m_currentValue) --;
	}
    if (i == 1 && (m_leverTrans.m_position.x + (float)m_leverSprite.m_source.w * 0.5f) + percentageUnit <= (m_position.m_position.x + m_sprite.m_source.w))
	{
		m_leverTrans.m_position.x += percentageUnit;
		(*m_currentValue) ++;
	}
}
bool GUISlider::Update(ImageLibrary& imageLibrary)
{
	if (*p_state == GUIObjectState::GOING_IN)
	{
		Ease(m_offscreen, m_menuscreen);
	}
	else if (*p_state == GUIObjectState::GOING_OUT)
	{
		Ease(m_menuscreen, m_offscreen);
	}
	if (m_number.m_value != *m_currentValue)
	{
		m_number.Reset(imageLibrary);
		m_number.Add(*m_currentValue, imageLibrary);
	}
	return false;
}
void GUISlider::ToggleHighlight(bool value, ImageLibrary& imageLibrary)
{

}

void GUISlider::Render(RenderManager& renderManager)
{
	renderManager.AddToHUDRenderObjects(&m_sprite, &m_position);
	renderManager.AddToHUDRenderObjects(&m_leverSprite, &m_leverTrans);
	m_number.Render(renderManager);
}