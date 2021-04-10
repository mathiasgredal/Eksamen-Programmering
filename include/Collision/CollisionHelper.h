#pragma once
#include "../Vec2d.h"
#include "Manifold.h"

class Circle;

namespace Util {
Manifold CreateManifoldCircleVsCircle(const Entity &entityA, const Circle* circleA,const Entity &entityB, const Circle* circleB);

}
