#include "../../include/Entity.h"
#include "../../include/Collision/Shape.h"
#include "../../include/Collision/Circle.h"
#include "../../include/Collision/Manifold.h"

Circle::Circle(float _radius)
{
    radius = _radius;
}

void Circle::Draw(NVGcontext *ctx, std::shared_ptr<Entity> entity) const
{
    nvgBeginPath(ctx);
    nvgCircle(ctx, entity->position.x, entity->position.y, radius);
    nvgFillColor(ctx, color);
    nvgFill(ctx);
}

Manifold Circle::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Shape *shapeB) const
{
    return shapeB->IsColliding(entityA, entityB, this);
}

Manifold Circle::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Circle *shapeB) const
{
    return Util::CreateManifoldCircleVsCircle(entityA, this, entityB, shapeB);
}

Manifold Circle::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Rectangle *shapeB) const
{
    // std::cout << "Circle vs Rect" << std::endl;
    Manifold manifold = Manifold();
    manifold.isColliding = false;
    return manifold;
}
