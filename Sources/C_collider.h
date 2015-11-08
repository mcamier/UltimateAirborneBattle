#ifndef _C_COLLIDER_H_
#define _C_COLLIDER_H_

#include "CPT_component.h"
#include "collisions_utils.h"

class Functor;

class CCollider : public IComponent {

public:
    const static ComponentType sk_componentType;
    
    ICollider *m_collider;
    bool m_callbackOncePerContact;
    bool m_bActivated;
    Functor *f_onCollisionCallback;

    CCollider(ICollider *collider, bool callbackOncePerContact, Functor *onCollisionFunctor) :
        m_collider(collider),
        m_callbackOncePerContact(callbackOncePerContact),
        f_onCollisionCallback(onCollisionFunctor),
        m_bActivated(true) {}

    virtual ~CCollider() {}

    inline const ComponentType getComponentType(void) const {
        return CCollider::sk_componentType;
    }

    static const char* getName(void) {
        return "CCollider";
    }

    IComponent* clone(void) const {
        return nullptr;
    }
};

#endif  