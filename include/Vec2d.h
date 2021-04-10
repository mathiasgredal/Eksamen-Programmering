#pragma once

class Vec2d
{
public:
    Vec2d();
	Vec2d(float _x, float _y);

	float x, y;

    float Length() const;
    Vec2d Normalized() const;

    Vec2d operator*(float a) const;
    Vec2d operator/(float a) const;

    Vec2d &operator+=(const Vec2d& a);
    Vec2d &operator-=(const Vec2d& a);

    Vec2d operator+(const Vec2d& a) const;
    Vec2d operator-(const Vec2d& a) const;
    static float Dot(const Vec2d& a, const Vec2d& b);
};
