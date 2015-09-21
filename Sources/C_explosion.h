#ifndef _C_EXPLOSION_H_
#define _C_EXPLOSION_H_

#include "CPT_component.h"
#include "CPT_vec2f.h"

class CExplosion : public IComponent {
public:
    const static ComponentType sk_componentType = 0x6a27a6c9;

public:
    int const static m_endCollideAt = 720;
    int m_lifetime;
    int m_elapsedLifetime;


    CExplosion() : 
        m_lifetime(1280),
        m_elapsedLifetime(0) {}

    virtual ~CExplosion() {}

    inline const ComponentType getComponentType(void) const {
        return CExplosion::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CExplosion";
    }
};

#endif