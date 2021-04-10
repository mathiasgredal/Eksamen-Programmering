#include "../include/Scene.h"

Scene::Scene()
{

}

Scene::Scene(std::vector<std::shared_ptr<Entity>> _entities)
{
    entities = _entities;
}

void Scene::Add(std::shared_ptr<Entity> entity)
{
    entities.push_back(entity);
}

std::vector<std::shared_ptr<Entity>> Scene::getEntities() const
{
    return entities;
}

void Scene::Step(float dT)
{
    for(auto& entity : entities) {
        std::vector<Manifold> collisions = {};

        // Check collisions
        for(auto& other : entities) {
            if(entity == other) continue;

            auto manifold = entity->IsColliding(other);
            if(manifold.isColliding) {
                entity->shape.get()->color = nvgRGBA(0, 255, 0, 122);
                collisions.push_back(manifold);
            }
        }

        if(entity->type == SimType::Dynamic) {
            // Resolve gravity
            entity->force += gravity_coeff * entity->mass;
            entity->velocity += entity->force / entity->mass * dT;

            // Resolve collisions with impulse
            for(auto& collision : collisions)
                collision.ResolveImpulse();

            // Resolve velocity
            entity->position += entity->velocity * dT;

            // Resolve collisions with position correction
            for(auto& collision : collisions)
                collision.ResolvePosition();

            // Clear forces
            entity->force = Vec2d();
        }

    }
}

