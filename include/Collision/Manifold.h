#pragma once

#include <memory>
#include <cmath>

#include "../Vec2d.h"
class Entity;

class Manifold {
public:
    std::shared_ptr<Entity> entityA;
    std::shared_ptr<Entity> entityB;

    Vec2d collisionPoint; // For now we only store 1 collisionpoint, but for polygons we might have multiple
    Vec2d normal; // Normal vector for the incident edge of the collision
    float depth; // Depth of the collision
    bool isColliding;
};
