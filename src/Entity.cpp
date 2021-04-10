#include "../include/Entity.h"

Entity::Entity(Vec2d _pos, float _rot, std::shared_ptr<Shape> _shape, std::string _name, SimType _type)
{
    position = _pos;
    rotation = _rot;
    shape = _shape;
    name = _name;
    type = _type;
}

Manifold Entity::IsColliding(std::shared_ptr<Entity> other)
{
    return shape->IsColliding(shared_from_this(), other, other->shape.get());
}

