#include "../../include/Collision/CollisionHelper.h"
#include "../../include/Collision/Circle.h"
#include "../../include/Entity.h"

Manifold Util::CreateManifoldCircleVsCircle(const Entity &entityA, const Circle *circleA, const Entity &entityB, const Circle *circleB)
{
    std::cout << "Test Circle Vs Circle collision" << std::endl;

    Manifold manifold = Manifold();
    // The incident normal must be the vector between the positions of the circles
    manifold.normal = entityA.position - entityB.position;

    // If the length of the "normal" is greater than the combined radius, then there is no collision
    float distance = manifold.normal.Length();
    float radius = circleA->radius + circleB->radius;
    if(distance >= radius) {
        std::cout << "No collision: d=" << distance << ", r=" << radius << std::endl;
        manifold.isColliding = false;
        return manifold;
    }

    std::cout << "Collision!!!"<< std::endl;

    manifold.depth = radius - distance;
    manifold.normal = manifold.normal / distance; // Creates a normalized vector or "enhedsvektor"
    manifold.collisionPointA = entityA.position + manifold.normal*circleA->radius;
    manifold.collisionPointA = entityB.position + manifold.normal*circleB->radius;
    manifold.entityA = &entityA;
    manifold.entityB = &entityB;
    return manifold;
}
