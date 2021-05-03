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

    nvgBeginPath(ctx);
    nvgMoveTo(ctx, entity->position.x, entity->position.y);
    nvgLineTo(ctx, entity->position.x + sin(entity->rotation) * radius, entity->position.y + cos(entity->rotation) * radius);
    nvgStrokeColor(ctx, nvgRGB(0,0,255));
    nvgStroke(ctx);
}

Manifold Circle::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Shape *shapeB) const
{
    return shapeB->IsColliding(entityB, entityA, this);
}

Manifold Circle::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Circle *shapeB) const
{
    return Util::CreateManifoldCircleVsCircle(entityA, this, entityB, shapeB);
}

Manifold Circle::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Rect *shapeB) const
{
    // std::cout << "Circle vs Rect" << std::endl;
    Manifold manifold = Manifold();
    manifold.isColliding = false;
    return manifold;
}

Manifold Circle::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Line *shapeB) const
{
    return Util::CreateManifoldCircleVsLine(entityA, this, entityB, shapeB);
}
