#ifndef _C_PHYSICS2D_H_
#define _C_PHYSICS2D_H_

#include "CPT_component.h"
#include "CPT_vec2f.h"

class CRigidBody : public IComponent {
public:
    const static ComponentType sk_componentType = 0x497e133a;

    Vec2f m_velocity;
    Vec2f m_acceleration;
    Vec2f m_forceAccum;

    bool m_bApplyGravity;

    float m_damping;

    CRigidBody(bool applyGravity) : 
        m_velocity(Vec2f()), 
        m_acceleration(Vec2f()),
        m_damping(0.70f), 
        m_forceAccum(Vec2f()), 
        m_bApplyGravity(applyGravity) {}

    CRigidBody(bool applyGravity, float damping) : 
        m_velocity(Vec2f()), 
        m_acceleration(Vec2f()), 
        m_damping(damping),
        m_forceAccum(Vec2f()), 
        m_bApplyGravity(applyGravity) {}

    virtual ~CRigidBody() {}

    inline const ComponentType getComponentType(void) const {
        return CRigidBody::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CRigidBody";
    }

    void addForce(Vec2f forceToAdd) {
        m_forceAccum += forceToAdd;
    }

    void clearForce(void) {
        m_forceAccum.setX(0);
        m_forceAccum.setY(0);
    }
};


#endif