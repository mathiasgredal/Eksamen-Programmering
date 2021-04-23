#pragma once

#include <memory>

#include "../Util.h"
#include "../Vec2d.h"
#include "Shape.h"
#include "CollisionHelper.h"

class Line : public Shape {
public:
    Line(float _a, float _b);
    float a;
    float b;
    void Draw(NVGcontext *ctx, std::shared_ptr<Entity> entity) const override;

    Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Shape *shapeB) const override;
    Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Circle *shapeB) const override;
    Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Rectangle *shapeB) const override;
    Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Line *shapeB) const override;
};
