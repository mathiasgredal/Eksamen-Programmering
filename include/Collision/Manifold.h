#pragma once

#include "../Vec2d.h"
class Entity;

class Manifold {
public:
    Manifold();

    const Entity* entityA;
    const Entity* entityB;

    Vec2d collisionPointA; // Point of furthest intrusion into entity B from entity A
    Vec2d collisionPointB; // Point of furthest intrusion into entity A from entity B
    Vec2d normal; // Normal vector for the incident edge of the collision
    float depth; // Depth of the collision
    bool isColliding;
};
