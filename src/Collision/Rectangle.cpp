#include "../../include/Entity.h"
#include "../../include/Collision/Shape.h"
#include "../../include/Collision/Rectangle.h"

Rectangle::Rectangle(float _width, float _height)
{
    width = _width;
    height = _height;
}

void Rectangle::Draw(NVGcontext *ctx, const Entity &entity) const
{
    nvgBeginPath(ctx);
    nvgRect(ctx, entity.position.x, entity.position.y, width, height);
    nvgFillColor(ctx, color);
    nvgFill(ctx);
}

bool Rectangle::IsColliding(const Entity &entityA, const Entity &entityB, const Shape *shapeB) const
{
    return shapeB->IsColliding(entityA, entityB, this);
}

bool Rectangle::IsColliding(const Entity &entityA, const Entity &entityB, const Circle *shapeB) const
{
    std::cout << "Rect vs Circle" << std::endl;
    return true;
}

bool Rectangle::IsColliding(const Entity &entityA, const Entity &entityB, const Rectangle *shapeB) const
{
    std::cout << "Rect vs Rect" << std::endl;
    return true;
}


