#include "../../include/Entity.h"
#include "../../include/Collision/Shape.h"
#include "../../include/Collision/Line.h"
#include "../../include/Collision/Manifold.h"


Line::Line(float _a, float _b)
{
    a = _a;
    b = _b;
}

void Line::Draw(NVGcontext *ctx, std::shared_ptr<Entity> entity) const
{
    nvgBeginPath(ctx);
    nvgMoveTo(ctx, 0, b);
    nvgLineTo(ctx, 10000, b + 10000*a);
    nvgStrokeColor(ctx, color);
    nvgStroke(ctx);
}

Manifold Line::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Shape *shapeB) const
{
    return shapeB->IsColliding(entityB, entityA, this);
}

Manifold Line::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Circle *shapeB) const
{
    return Util::CreateManifoldCircleVsLine(entityB, shapeB, entityA, this);
}

Manifold Line::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Rect *shapeB) const
{
    // std::cout << "Rect vs Rect" << std::endl;
    Manifold manifold = Manifold();
    manifold.isColliding = false;
    return manifold;
}

Manifold Line::IsColliding(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB, const Line *shapeB) const
{
    Manifold manifold = Manifold();
    manifold.isColliding = false;
    return manifold;
}


