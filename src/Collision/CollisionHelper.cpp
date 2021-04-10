#include "../../include/Collision/CollisionHelper.h"
#include "../../include/Collision/Circle.h"
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
