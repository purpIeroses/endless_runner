#include "Transform.h"

Transform::Transform(): m_position(Vector2(0,0)), m_scale(Vector2(0,0)), m_angle(0){}
Transform::Transform(Vector2 position) : m_position(position), m_scale(Vector2(0, 0)), m_angle(0) {}
Transform::Transform(Vector2 position, Vector2 scale) : m_position(position), m_scale(scale), m_angle(0) {}
Transform::Transform(Vector2 position, int angle) : m_position(position), m_scale(Vector2(0, 0)), m_angle(angle) {}

void Transform::SetPosition(const float x, const float y)
{
	m_position.x = x;
	m_position.y = y;
}

void Transform::ChangePosition(const float x, const float y)
{
	m_position.x += x;
	m_position.y += y;
}

void Transform::SetScale(const float x, const float y)
{
	this->m_scale.x = x;
	this->m_scale.y = y;
}