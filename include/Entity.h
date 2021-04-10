#pragma once

#include "Vec2d.h"
#include "Collision/Manifold.h"
#include "Collision/Shape.h"

class Entity
{
public:
    Entity(Vec2d _pos, float _rot, std::shared_ptr<Shape> _shape);

    std::shared_ptr<Shape> shape;
    Vec2d position;
    float rotation;
    Vec2d force;

    Vec2d velocity;
    float mass = 1;

    bool IsColliding(const Entity& other);
    Manifold CreateManifold(const Entity& other);
};
