#include "../include/Entity.h"

Entity::Entity(Vec2d _pos, float _rot, std::shared_ptr<Shape> _shape, SimType _type)
{
    position = _pos;
    rotation = _rot;
    shape = _shape;
    type = _type;
}

bool Entity::IsColliding(const Entity &other)
{
    return this->shape->IsColliding(*this, other, other.shape.get());
}

Manifold Entity::CreateManifold(const Entity &other)
{
    return Manifold();
}

