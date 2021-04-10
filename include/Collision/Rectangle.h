#pragma once

#include "../Vec2d.h"
#include "Shape.h"

class Rectangle : public Shape {
public:
    Rectangle(float _width, float _height);
    float width, height;
    void Draw(NVGcontext *ctx, const Entity &entity) const override;

    bool IsColliding(const Entity &entityA, const Entity &entityB, const Shape *shapeB) const override;
    bool IsColliding(const Entity &entityA, const Entity &entityB, const Circle *shapeB) const override;
    bool IsColliding(const Entity &entityA, const Entity &entityB, const Rectangle *shapeB) const override;
};
