#pragma once

#include <nanovg.h>

#include "../Vec2d.h"
class Entity;
class Circle;
class Rectangle;

class Shape 
{
public:
    NVGcolor color = nvgRGB(255, 0, 0);
    virtual void Draw(NVGcontext* ctx, const Entity& entity) const = 0;

    virtual bool IsColliding(const Entity& entityA, const Entity& entityB, const Shape* shapeB) const = 0;
    virtual bool IsColliding(const Entity& entityA, const Entity& entityB, const Circle* shapeB) const = 0;
    virtual bool IsColliding(const Entity& entityA, const Entity& entityB, const Rectangle* shapeB) const = 0;
};
