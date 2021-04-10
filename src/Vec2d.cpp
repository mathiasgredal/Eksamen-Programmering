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

Vec2d Vec2d::operator*(float a)
{
    return Vec2d(x*a, y*a);
}

Vec2d Vec2d::operator/(float a)
{
    return Vec2d(x/a, y/a);
}

Vec2d& Vec2d::operator+=(const Vec2d& a)
{
    x += a.x;
    y += a.y;
    return *this;
}
