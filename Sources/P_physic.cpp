#include "P_physic.h"

#include "C_transform.h"
#include "C_rigidbody.h"

ComponentType f[] = { CRigidBody::sk_componentType, CTransform::sk_componentType };
const std::vector<ComponentType> PPhysics2D::sk_requirements(f, f + 2);

void PPhysics2D::v_destroy() {
}

void PPhysics2D::v_process(entityID id, const GameTime& gameTime) {
    CRigidBody *body = getEntityAs<CRigidBody>(id);
    CTransform *transform = getEntityAs<CTransform>(id);

    transform->m_position.addScaledVector(body->m_velocity, gameTime.getElapsedSecond());
    if (body->m_bApplyGravity) {
        body->addForce(Vec2f(0, 150.0f));
    }
    body->m_velocity.addScaledVector(body->m_forceAccum, gameTime.getElapsedSecond());

    body->m_velocity *= powf(body->m_damping, gameTime.getElapsedSecond());

    body->clearForce();
}