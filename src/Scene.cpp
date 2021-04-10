#include "../include/Scene.h"

Scene::Scene()
{

}

Scene::Scene(std::vector<Entity> _entities)
{
    entities = _entities;
}

void Scene::Add(const Entity &entity)
{
    entities.push_back(entity);
}

std::vector<Entity> Scene::getEntities() const
{
    return entities;
}

void Scene::Step(float dT)
{
    std::vector<Manifold> collisions = {};
    for(auto& entity : entities) {
        // Check collisions
        std::cout << "Collisions" << std::endl;
        for(const auto& other : entities) {
            if(&entity == &other) continue;

            if(entity.IsColliding(other))
                entity.shape.get()->color = nvgRGB(0, 255, 0);

                //collisions.push_back(entity.CreateManifold(other));

        }

        // Resolve gravity
        entity.force += gravity_coeff * entity.mass;
        entity.velocity += entity.force / entity.mass * dT;
        entity.position += entity.velocity * dT;
        entity.force = Vec2d();
    }
}

