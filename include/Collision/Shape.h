#pragma once

#include <memory>
#include <nanovg.h>

#include "../Vec2d.h"
class Entity;
class Circle;
class RectShape;
class Line;
class Manifold;

class Shape 
{
public:
    NVGcolor color = nvgRGB(255, 0, 0);
    virtual void Draw(NVGcontext* ctx, std::shared_ptr<Entity> entity) const = 0;

    virtual Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Shape* shapeB) const = 0;
    virtual Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Circle* shapeB) const = 0;
    virtual Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const RectShape* shapeB) const = 0;
    virtual Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Line *shapeB) const = 0;
};
