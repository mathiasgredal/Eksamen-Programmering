#pragma once

#include <memory>

#include "../Vec2d.h"
#include "Shape.h"

class Rect : public Shape {
public:
    Rect(float _width, float _height);
    float width, height;
    void Draw(NVGcontext *ctx, std::shared_ptr<Entity> entity) const override;

    Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Shape *shapeB) const override;
    Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Circle *shapeB) const override;
    Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Rect *shapeB) const override;
    Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Line *shapeB) const override;
};
