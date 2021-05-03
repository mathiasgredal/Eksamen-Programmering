#pragma once

#include "../Util.h"
#include "../Vec2d.h"
#include "Shape.h"
#include "CollisionHelper.h"

class Circle : public Shape {
public:
    Circle(float _radius);
    float radius;
    void Draw(NVGcontext *ctx, std::shared_ptr<Entity> entity) const override;

    Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Shape *shapeB) const override;
    Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Circle *shapeB) const override;
    Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Rect *shapeB) const override;
    Manifold IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Line *shapeB) const override;
};
