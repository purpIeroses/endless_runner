#ifndef TRANSFORM_H_DEFINED
#define TRANSFORM_H_DEFINED

#include "Vector2.h"

struct Transform
{
	Vector2 m_position;
	Vector2 m_scale;
	unsigned int m_angle;
	Transform();
	Transform(Vector2 position);
	Transform(Vector2 position, Vector2 scale);
	Transform(Vector2 position, int angle);

	void SetPosition(const float x, const float y);
	void ChangePosition(const float x, const float y);
	void SetScale(const float x, const float y);
};

#endif