#pragma once

#include <iostream>
#include <vector>
#include "Entity.h"

class Scene 
{
public:
    Scene();
    Scene(std::vector<Entity> _entities);
    void Add(const Entity& entity);
    void Step(float dT);
    std::vector<Entity> getEntities() const;

private:
    std::vector<Entity> entities = {};
    Vec2d gravity_coeff = Vec2d(0, 9.82*6);

};
