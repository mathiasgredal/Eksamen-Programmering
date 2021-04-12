#include "../include/Entity.h"

Entity::Entity(Vec2d _pos, std::shared_ptr<Shape> _shape)
{
    position = _pos;
    shape = _shape;
}

Manifold Entity::IsColliding(std::shared_ptr<Entity> other)
{
    return shape->IsColliding(shared_from_this(), other, other->shape.get());
}

