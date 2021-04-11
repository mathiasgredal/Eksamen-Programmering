#include "../../include/Entity.h"
#include "../../include/Collision/Shape.h"
#include "../../include/Collision/Rectangle.h"
#include "../../include/Collision/Manifold.h"


Rectangle::Rectangle(float _width, float _height)
{
    width = _width;
    height = _height;
}

void Rectangle::Draw(NVGcontext *ctx, std::shared_ptr<Entity> entity) const
{
    nvgBeginPath(ctx);
    nvgRect(ctx, entity->position.x, entity->position.y, width, height);
    nvgFillColor(ctx, color);
    nvgFill(ctx);
}

Manifold Rectangle::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Shape *shapeB) const
{
    return shapeB->IsColliding(entityB, entityA, this);
}

Manifold Rectangle::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Circle *shapeB) const
{
    // std::cout << "Rect vs Circle" << std::endl;
    Manifold manifold = Manifold();
    manifold.isColliding = false;
    return manifold;
}

Manifold Rectangle::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Rectangle *shapeB) const
{
    // std::cout << "Rect vs Rect" << std::endl;
    Manifold manifold = Manifold();
    manifold.isColliding = false;
    return manifold;
}

Manifold Rectangle::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Line *shapeB) const
{
    Manifold manifold = Manifold();
    manifold.isColliding = false;
    return manifold;
}


