#pragma once

#include "Vec2d.h"
#include "Collision/Manifold.h"
#include "Collision/Shape.h"

enum SimType {Dynamic, Static, Ghost};

class Entity : public std::enable_shared_from_this<Entity>
{
public:
    Entity(Vec2d _pos,
           float _rot,
           std::shared_ptr<Shape> _shape,
           float _mass = 1,
           float _restitution = 1,
           SimType _type = SimType::Dynamic);

    Vec2d position;
    float rotation;
    std::shared_ptr<Shape> shape;

    Vec2d force;

    Vec2d velocity;
    float mass;
    float restitution;
    SimType type;

    Manifold IsColliding(std::shared_ptr<Entity> other);
};
