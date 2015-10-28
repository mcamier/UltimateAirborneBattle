#ifndef _C_PHYSICS2D_H_
#define _C_PHYSICS2D_H_

#include "glm/vec2.hpp"
#include "CPT_component.h"

class CRigidBody : public IComponent {
public:
    const static ComponentType sk_componentType;

    glm::vec2   m_velocity;
    glm::vec2   m_acceleration;
    glm::vec2   m_forceAccum;

    bool        m_bApplyGravity;

    float       m_damping;

    CRigidBody(bool applyGravity) : 
        m_velocity(glm::vec2()),
        m_acceleration(glm::vec2()),
        m_damping(0.70f), 
        m_forceAccum(glm::vec2()),
        m_bApplyGravity(applyGravity) {}

    CRigidBody(bool applyGravity, float damping) : 
        m_velocity(glm::vec2()),
        m_acceleration(glm::vec2()),
        m_damping(damping),
        m_forceAccum(glm::vec2()),
        m_bApplyGravity(applyGravity) {}

    virtual ~CRigidBody() {}

    inline const ComponentType getComponentType(void) const {
        return CRigidBody::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CRigidBody";
    }

    void addForce(glm::vec2 forceToAdd) {
        m_forceAccum += forceToAdd;
    }

    void clearForce(void) {
        m_forceAccum.x = 0.0f;
        m_forceAccum.y = 0.0f;
    }
};


#endif