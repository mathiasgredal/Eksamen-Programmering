#include "../../include/Entity.h"
#include "../../include/Collision/Shape.h"
#include "../../include/Collision/Rect.h"
#include "../../include/Collision/Manifold.h"


Rect::Rect(float _width, float _height)
{
    width = _width;
    height = _height;
}

void Rect::Draw(NVGcontext *ctx, std::shared_ptr<Entity> entity) const
{
    nvgBeginPath(ctx);
    nvgRect(ctx, entity->position.x, entity->position.y, width, height);
    nvgFillColor(ctx, color);
    nvgFill(ctx);
}

Manifold Rect::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Shape *shapeB) const
{
    return shapeB->IsColliding(entityB, entityA, this);
}

Manifold Rect::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Circle *shapeB) const
{
    // std::cout << "Rect vs Circle" << std::endl;
    Manifold manifold = Manifold();
    manifold.isColliding = false;
    return manifold;
}

Manifold Rect::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Rect *shapeB) const
{
    // std::cout << "Rect vs Rect" << std::endl;
    Manifold manifold = Manifold();
    manifold.isColliding = false;
    return manifold;
}

Manifold Rect::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Line *shapeB) const
{
    Manifold manifold = Manifold();
    manifold.isColliding = false;
    return manifold;
}


