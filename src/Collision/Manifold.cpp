#include "../../include/Collision/Manifold.h"
#include "../../include/Entity.h"

Manifold::Manifold()
{

}

void Manifold::Resolve()
{
    std::cout << "Resolving collision" << std::endl;
    const bool staticA = entityA->type == SimType::Static;
    const bool staticB = entityB->type == SimType::Static;

    if(staticA && staticB) // Both entities are static, no need for collision resolution
        return;

    // We zero out velocity if static
    Vec2d velocityA = staticA? Vec2d() : entityA->velocity;
    Vec2d velocityB = staticB? Vec2d() : entityB->velocity;

    // TODO: Relative velocity should take angulare velocity into account using distance from contact point
    Vec2d relativeVelocity = velocityB - velocityA;

    // We can find the speed of the entities relative to the contact point by
    // projecting the relative velocity onto the normal vector.
    // Since the normal vector is normalized, we just use the dot product
    // (see: https://www.webmatematik.dk/lektioner/sarligt-for-htx/vektorer-i-planen/projektion-fra-enhedsvektor)
    float contactSpeed = Vec2d::Dot(relativeVelocity, normal);

    // Negative velocity means the entities are moving away from each other
    // In that case there is no need for collision resolution
    if(contactSpeed < 0)
        return;

    // Calculate a combined restitution or bounciness
    float e = 1;

    // Create an impulse scalar(still need to account for mass and moment of inertia)
    float j = -(1+e)*contactSpeed/(2);

    std::cout << "NAMES: A=" << entityA->name << ", B=" << entityB->name << std::endl;
    std::cout << "VELOCITY A: " << velocityA.x << ", " << velocityA.y << std::endl;
    std::cout << "VELOCITY B: " << velocityB.x << ", " << velocityB.y << std::endl;
    std::cout << "RELATIVE VELOCITY: " << relativeVelocity.x << ", " << relativeVelocity.y << std::endl;
    std::cout << "CONTACT SPEED: " << contactSpeed << std::endl;
    std::cout << "IMPULSE SCALAR: " << j << std::endl;

    Vec2d impulse = normal * j;

    // Use impulse to modify speed
    // TODO: account for mass
    entityA->velocity -= impulse;
    entityB->velocity += impulse;

    return;
}
