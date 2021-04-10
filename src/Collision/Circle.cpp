#include "../../include/Entity.h"
#include "../../include/Collision/Shape.h"
#include "../../include/Collision/Circle.h"

Circle::Circle(float _radius)
{
    radius = _radius;
}

void Circle::Draw(NVGcontext *ctx, const Entity &entity) const
{
    nvgBeginPath(ctx);
    nvgCircle(ctx, entity.position.x, entity.position.y, radius);
    nvgFillColor(ctx, color);
    nvgFill(ctx);
}

bool Circle::IsColliding(const Entity &entityA, const Entity &entityB, const Shape *shapeB) const
{
    return shapeB->IsColliding(entityA, entityB, this);
}

bool Circle::IsColliding(const Entity &entityA, const Entity &entityB, const Circle *shapeB) const
{
    auto manifold = Util::CreateManifoldCircleVsCircle(entityA, this, entityB, shapeB);

    if(manifold.isColliding)
        std::cout << "WE HAVE A COLLISION" << std::endl;

    return manifold.isColliding;
}

bool Circle::IsColliding(const Entity &entityA, const Entity &entityB, const Rectangle *shapeB) const
{
//    std::cout << "Circle vs Rect" << std::endl;
    return true;
}
