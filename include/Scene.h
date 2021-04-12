#pragma once

#include <iostream>
#include <vector>
#include "Entity.h"
#include "Resolver.h"

class Scene 
{
public:
    Scene();
    Scene(std::vector<std::shared_ptr<Entity>> _entities);
    void Add(std::shared_ptr<Entity> entity);
    void Step(float dT);
    std::vector<std::shared_ptr<Entity>> getEntities() const;

private:
    std::vector<std::shared_ptr<Entity>> entities = {};
    Vec2d gravity_coeff = Vec2d(0, 9.82*6);

};
