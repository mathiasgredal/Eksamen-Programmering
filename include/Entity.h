#pragma once

#include "Vec2d.h"
#include "Collision/Manifold.h"
#include "Collision/Shape.h"

enum SimType {Dynamic, Static, Ghost};

class Entity : public std::enable_shared_from_this<Entity>
{
public:
    Entity(Vec2d _pos, float _rot, std::shared_ptr<Shape> _shape, std::string _name = "", SimType _type = SimType::Dynamic);

    std::string name = "";
    std::shared_ptr<Shape> shape;
    Vec2d position;
    float rotation;
    Vec2d force;

    Vec2d velocity;
    float mass = 1;
    SimType type = SimType::Dynamic;

    Manifold IsColliding(std::shared_ptr<Entity> other);
};
