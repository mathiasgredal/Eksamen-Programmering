#pragma once

class Vec2d
{
public:
    Vec2d();
	Vec2d(float _x, float _y);

	float x, y;

    Vec2d operator*(float a);
    Vec2d operator/(float a);

    Vec2d &operator+=(const Vec2d& a);
};
