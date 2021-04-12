#pragma once
#include <memory>

class Manifold;

namespace Util {
    void ResolveImpulse(Manifold& manifold);
    void ResolvePosition(Manifold& manifold);
}
