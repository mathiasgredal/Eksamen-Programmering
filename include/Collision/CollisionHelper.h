#pragma once

#include "../Vec2d.h"
#include "Manifold.h"

class Circle;
class Line;

namespace Util {
Manifold CreateManifoldCircleVsCircle(std::shared_ptr<Entity> entityA, const Circle* circleA, std::shared_ptr<Entity> entityB, const Circle* circleB);
Manifold CreateManifoldCircleVsLine(std::shared_ptr<Entity> entityA, const Circle* circleA, std::shared_ptr<Entity> entityB, const Line* lineB);
}
