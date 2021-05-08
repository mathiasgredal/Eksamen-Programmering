#include "../../include/Collision/CollisionHelper.h"
#include "../../include/Collision/Circle.h"
#include "../../include/Collision/Line.h"
#include "../../include/Entity.h"

Manifold Util::CreateManifoldCircleVsCircle(std::shared_ptr<Entity> entityA, const Circle *circleA, std::shared_ptr<Entity> entityB, const Circle *circleB)
{
    Manifold manifold = Manifold();
    // The incident normal must be the vector between the positions of the circles
    manifold.normal = entityA->position - entityB->position;

    // If the length of the "normal" is greater than the combined radius, then there is no collision
    float distance = manifold.normal.Length();
    float radius = circleA->radius + circleB->radius;
    if(distance >= radius) {
        manifold.isColliding = false;
        return manifold;
    }

    manifold.isColliding = true;
    manifold.depth = radius - distance;
    manifold.normal = manifold.normal / distance; // Creates a normalized vector or "enhedsvektor"
    manifold.collisionPoint = entityA->position + manifold.normal*circleA->radius;
    manifold.entityA = entityA;
    manifold.entityB = entityB;
    return manifold;
}

Manifold Util::CreateManifoldCircleVsLine(std::shared_ptr<Entity> entityA, const Circle *circleA, std::shared_ptr<Entity> entityB, const Line *lineB)
{
    Manifold manifold = Manifold();

    // Create normal vector
    const Vec2d dir = Vec2d(0, lineB->b) - Vec2d(1, lineB->a + lineB->b);
    manifold.normal = Vec2d(dir.y, -dir.x).Normalized();

    // Create vector between circle and line and project on normal vector to find distance
    const Vec2d circToLine = Vec2d(0, lineB->b) - entityA->position;
    float distance = Vec2d::Dot(circToLine, manifold.normal);

    if(distance - circleA->radius <= 0) {
        // We have a collision
        manifold.isColliding = true;
        manifold.depth = abs(distance - circleA->radius);
        manifold.collisionPoint = entityA->position - manifold.normal * manifold.depth;
        manifold.entityA = entityB;
        manifold.entityB = entityA;
    } else {
        manifold.isColliding = false;
    }

    return manifold;
}
