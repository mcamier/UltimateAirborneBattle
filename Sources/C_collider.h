#ifndef _C_COLLIDER_H_
#define _C_COLLIDER_H_

#include "CPT_component.h"

class Functor;

class CCollider : public IComponent {

public:
    const static ComponentType sk_componentType = 0x6b47e35;
    
    int m_radius;

    int m_colliderLayer;
    bool m_bActivated;
    Functor *f_onCollisionCallback;

    CCollider(int colliderLayer, int radius, Functor *onCollisionFunctor) :
        m_radius(radius), 
        m_colliderLayer(colliderLayer),
        f_onCollisionCallback(onCollisionFunctor),
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