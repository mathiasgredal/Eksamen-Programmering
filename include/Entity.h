#pragma once

#include "Vec2d.h"
#include "Collision/Manifold.h"
#include "Collision/Shape.h"

enum SimType {Dynamic, Static, Ghost};

class Entity : public std::enable_shared_from_this<Entity>
{
public:
    Entity(Vec2d _pos, std::shared_ptr<Shape> _shape);

    // Translational motion
    Vec2d position = Vec2d(0, 0);
    Vec2d velocity = Vec2d(0, 0);
    Vec2d force = Vec2d(0, 0);

    // Rotational motion
    float rotation = 0;
    float angularVelocity = 0;
    float torque = 0;

    // Dynamics
    float mass = 1;
    float momentOfInertia = 1;
    float restitution = 1;
    float staticFriction = 0.1;
    float dynamicFriction = 0.1;
    std::shared_ptr<Shape> shape;
    SimType type = SimType::Dynamic;

    Manifold IsColliding(std::shared_ptr<Entity> other);
};
