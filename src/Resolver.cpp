#include "../include/Resolver.h"
#include "../include/Collision/Manifold.h"
#include "../include/Entity.h"


void Util::ResolveImpulse(Manifold &m)
{
    // Formulas can be found here: http://www.chrishecker.com/images/e/e7/Gdmphys3.pdf
    const bool staticA = m.entityA->type == SimType::Static;
    const bool staticB = m.entityB->type == SimType::Static;

    if(staticA && staticB) // Both entities are static, no need for collision resolution
        return;

    // We zero out velocity if static
    if(staticA)
        m.entityA->velocity = Vec2d();
    if(staticB)
        m.entityB->velocity = Vec2d();

    // Equation 7 from the linked pdf
    Vec2d relativeVelocity = m.entityB->velocity - m.entityA->velocity;

    // We can find the speed of the entities relative to the contact point by
    // projecting the relative velocity onto the normal vector.
    // Since the normal vector is normalized, we just use the dot product
    // (see: https://www.webmatematik.dk/lektioner/sarligt-for-htx/vektorer-i-planen/projektion-fra-enhedsvektor)
    // Also eq. 2 from pdf
    float contactSpeed = Vec2d::Dot(relativeVelocity, m.normal);

    // Negative velocity means the entities are moving away from each other
    // In that case there is no need for collision resolution
    if(contactSpeed < 0)
        return;

    // Calculate a combined restitution or bounciness
    float e = m.entityA->restitution*m.entityB->restitution;

    // Create an impulse scalar (eq. 6 from pdf)
    // NOTE: The formula has been changed from eq. 6 to use contact speed instead of relative velocity
    // This makes it a litte simpler, but we have to use a square root for normalization, which inhibits a performance penalty
    float j = -(1+e)*contactSpeed/(1/m.entityA->mass + 1/m.entityB->mass);

    // Eq. 8.a to calculate speed change from impulse
    Vec2d impulseA = (m.normal * j)/m.entityA->mass;
    Vec2d impulseB = (m.normal * j)/m.entityB->mass;

    // From newtons third law, an action has an opposite reaction, therefore
    // when we add velocity to one object we remove from another
    m.entityA->velocity -= impulseA;
    m.entityB->velocity += impulseB;

    // Calculate friction
    // Since we have updated the velocoties, we need to redo the earlier calculations
    if(staticA) {
        m.entityA->velocity = Vec2d();
    }
    if(staticB) {
        m.entityB->velocity = Vec2d();
    }
    relativeVelocity = m.entityB->velocity - m.entityA->velocity;
    contactSpeed = Vec2d::Dot(relativeVelocity, m.normal);

    // We create a tangent vector to the incident face, which descripes the friction force direction
    Vec2d tangent = (relativeVelocity - m.normal * contactSpeed ).Normalized();

    // By projection the relative velocity onto the tangent we get the "sliding" speed
    float frictionSpeed = Vec2d::Dot(relativeVelocity, tangent);

    float staticFriction = sqrt(m.entityA->staticFriction * m.entityB->staticFriction);
    float dynamicFriction = sqrt(m.entityA->dynamicFriction * m.entityB->dynamicFriction);

    // Calculate scalar for friction impulse
    float fj = -frictionSpeed / (1/m.entityA->mass + 1/m.entityB->mass);

    // Dont apply small friction impulses, as it causes jitter
    if(abs(fj) < 0.001)
        return;

    Vec2d friction;
    if(abs(fj) < j * staticFriction)
        friction = tangent * fj; // If the friction is small, then static friciton applies
    else
        friction = tangent * -j * dynamicFriction; // otherwise dynamic friciton

    // Apply friction impulses
    if(!staticA)
        m.entityA->velocity += friction/m.entityA->mass;
    if(!staticB)
        m.entityB->velocity -= friction/m.entityB->mass;
}

void Util::ResolvePosition(Manifold &m)
{
    // Position resolution is about reducing the penetration depth a certain percantage
    // to prevent objects from sinking
    float maxDepth= 0.1f;
    float correctionPercentage = 0.5f;
    float correctionScalar = (std::max(m.depth - maxDepth, 0.0f)*m.entityA->mass*m.entityB->mass/(m.entityA->mass + m.entityB->mass));
    Vec2d correction = m.normal * correctionScalar * correctionPercentage;
    m.entityA->position += m.entityA->type == SimType::Dynamic? correction / m.entityA->mass : Vec2d();
    m.entityB->position -= m.entityB->type == SimType::Dynamic? correction / m.entityB->mass : Vec2d();
}
