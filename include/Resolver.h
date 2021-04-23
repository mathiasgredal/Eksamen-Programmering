#pragma once
#include <memory>
#include <imgui.h>
#include <fmt/core.h>


class Manifold;

namespace Util {
    void ResolveImpulse(Manifold& manifold);
    void ResolvePosition(Manifold& manifold);
}
