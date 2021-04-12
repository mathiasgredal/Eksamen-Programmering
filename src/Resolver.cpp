#include "../include/Resolver.h"
#include "../include/Collision/Manifold.h"
#include "../include/Entity.h"


void Util::ResolveImpulse(Manifold &m)
{
    const bool staticA = m.entityA->type == SimType::Static;
    const bool staticB = m.entityB->type == SimType::Static;

    if(staticA && staticB) // Both entities are static, no need for collision resolution
        return;

    // We zero out velocity if static
    Vec2d velocityA = staticA? Vec2d() : m.entityA->velocity;
    Vec2d velocityB = staticB? Vec2d() : m.entityB->velocity;

    // TODO: Relative velocity should take angulare velocity into account using distance from contact point
    Vec2d relativeVelocity = velocityB - velocityA;

    // We can find the speed of the entities relative to the contact point by
    // projecting the relative velocity onto the normal vector.
    // Since the normal vector is normalized, we just use the dot product
    // (see: https://www.webmatematik.dk/lektioner/sarligt-for-htx/vektorer-i-planen/projektion-fra-enhedsvektor)
    float contactSpeed = Vec2d::Dot(relativeVelocity, m.normal);

    // We should precalculate the inverse mass in the constructor
    float inverseMassA = 1/m.entityA->mass;
    float inverseMassB = 1/m.entityB->mass;

    // Negative velocity means the entities are moving away from each other
    // In that case there is no need for collision resolution
    if(contactSpeed < 0)
        return;

    // Calculate a combined restitution or bounciness
    float e = m.entityA->restitution*m.entityB->restitution;

    // Create an impulse scalar
    float j = -(1+e)*contactSpeed/(inverseMassA + inverseMassB);

    Vec2d impulse = m.normal * j;

    // Use impulse to modify speed
    m.entityA->velocity -= impulse * inverseMassA;
    m.entityB->velocity += impulse * inverseMassB;

    // Calculate friction
    // Since we have updated the velocoties, we need to redo the earlier calculations
    velocityA = staticA? Vec2d() : m.entityA->velocity;
    velocityB = staticB? Vec2d() : m.entityB->velocity;
    relativeVelocity = velocityB - velocityA;
    contactSpeed = Vec2d::Dot(relativeVelocity, m.normal);

    // We create a tangent vector to the incident face, which descripes the friction force direction
    Vec2d tangent = (relativeVelocity - m.normal * contactSpeed ).Normalized();

    // By projection the relative velocity onto the tangent we get the "sliding" speed or friction speed
    float frictionSpeed = Vec2d::Dot(relativeVelocity, tangent);

    float staticFriction = sqrt(m.entityA->staticFriction * m.entityB->staticFriction);
    float dynamicFriction = sqrt(m.entityA->dynamicFriction * m.entityB->dynamicFriction);

    // Calculate scalar for friction impulse
    float fj = -frictionSpeed / (inverseMassA + inverseMassB);

    if(abs(fj) < 0.001)
        return;

    Vec2d friction;
    if(abs(fj) < j * staticFriction)
        friction = tangent * fj; // If the friction is small, then static friciton applies
    else
        friction = tangent * -j * dynamicFriction; // otherwise dynamic friciton

    // Apply friction impulses
    if(!staticA)
        m.entityA->velocity += friction * inverseMassA;
    if(!staticB)
        m.entityB->velocity -= friction * inverseMassB;
}

void Util::ResolvePosition(Manifold &m)
{
    // Position resolution is about reducing the penetration depth a certain percantage
    // to prevent objects from sinking
    float maxDepth= 0.05f;
    float correctionPercentage = 0.4f;
    float correctionScalar = (std::max(m.depth - maxDepth, 0.0f)*m.entityA->mass*m.entityB->mass/(m.entityA->mass + m.entityB->mass));
    Vec2d correction = m.normal * correctionScalar * correctionPercentage;
    m.entityA->position += m.entityA->type == SimType::Dynamic? correction / m.entityA->mass : Vec2d();
    m.entityB->position -= m.entityB->type == SimType::Dynamic? correction / m.entityB->mass : Vec2d();
}
