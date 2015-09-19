#ifndef _C_COLLIDER_H_
#define _C_COLLIDER_H_

#include "CPT_component.h"

class Functor;

class CCollider : public IComponent {

public:
    const static ComponentType sk_componentType = 0x6b47e35;
    
    Functor *f_onCollisionFunctor;
    int m_colliderIndex;
    int m_radius;
    bool m_bActivated;

    CCollider(int colliderIndex, int radius, Functor *onCollisionFunctor) :
        m_radius(radius), 
        m_colliderIndex(colliderIndex), 
        f_onCollisionFunctor(onCollisionFunctor),
        m_bActivated(true) {}

    virtual ~CCollider() {}

    inline const ComponentType getComponentType(void) const {
        return CCollider::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CCollider";
    }
};

#endif