#ifndef VECTOR2_H_DEFINED
#define VECTOR2_H_DEFINED

struct Vector2
{
	float x;
	float y;
	Vector2(float n_x, float n_y);

	Vector2 operator+(const Vector2& rhs) const;
};

#endif