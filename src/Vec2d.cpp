#include "../include/Vec2d.h"

Vec2d::Vec2d()
{
    x = 0;
    y = 0;
}

Vec2d::Vec2d(float _x, float _y)
{
    x = _x;
    y = _y;
}

float Vec2d::Length() const
{
    return std::sqrt(x*x+y*y);
}

Vec2d Vec2d::operator*(float a) const
{
    return Vec2d(x*a, y*a);
}

Vec2d Vec2d::operator/(float a) const
{
    return Vec2d(x/a, y/a);
}

Vec2d& Vec2d::operator+=(const Vec2d& a)
{
    x += a.x;
    y += a.y;
    return *this;
}

Vec2d &Vec2d::operator-=(const Vec2d &a)
{
    x -= a.x;
    y -= a.y;
    return *this;
}

Vec2d Vec2d::operator+(const Vec2d &a) const
{
    return Vec2d(x + a.x, y + a.y);
}

Vec2d Vec2d::operator-(const Vec2d &a) const
{
    return Vec2d(x - a.x, y - a.y);
}

float Vec2d::Dot(const Vec2d &a, const Vec2d &b)
{
    return a.x * b.x + a.y * b.y;
}
