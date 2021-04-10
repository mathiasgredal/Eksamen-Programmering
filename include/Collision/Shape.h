#pragma once

#include <nanovg.h>

#include "../Vec2d.h"
class Entity;
class Circle;
class Rectangle;
class Manifold;

class Shape 
{
public:
    NVGcolor color = nvgRGB(255, 0, 0);
    virtual void Draw(NVGcontext* ctx, std::shared_ptr<Entity> entity) const = 0;

    virtual Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Shape* shapeB) const = 0;
    virtual Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Circle* shapeB) const = 0;
    virtual Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Rectangle* shapeB) const = 0;
};
