#include "Vector2.h"
#include <cmath>

Vector2::Vector2(float n_x, float n_y)
{
	x = n_x; y = n_y;
}
Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}