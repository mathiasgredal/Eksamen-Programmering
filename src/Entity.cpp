#include "../include/Entity.h"

Entity::Entity(Vec2d _pos, float _rot, std::shared_ptr<Shape> _shape)
{
    position = _pos;
    rotation = _rot;
    shape = _shape;
}

bool Entity::IsColliding(const Entity &other)
{
    this->shape->IsColliding(*this, other, other.shape.get());
    return true;
}

Manifold Entity::CreateManifold(const Entity &other)
{
    return Manifold();
}

