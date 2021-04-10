#include "../include/Entity.h"

Entity::Entity(Vec2d _pos, float _rot, std::shared_ptr<Shape> _shape, float _mass, float _restitution, float _staticFriction, float _dynamicFriction, SimType _type)
{
    position = _pos;
    rotation = _rot;
    mass = _mass;
    restitution = _restitution;
    staticFriction = _staticFriction;
    dynamicFriction = _dynamicFriction;
    shape = _shape;
    type = _type;
}

Manifold Entity::IsColliding(std::shared_ptr<Entity> other)
{
    return shape->IsColliding(shared_from_this(), other, other->shape.get());
}

