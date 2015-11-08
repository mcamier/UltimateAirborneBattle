#ifndef _C_EXPLOSION_H_
#define _C_EXPLOSION_H_

#include "CPT_component.h"
#include "CPT_creator.h"
#include "rapidxml\rapidxml.hpp"

class CExplosion : public IComponent {
public:
    const static ComponentType sk_componentType;

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

    static const char* getName(void) {
        return "CExplosion";
    }

    IComponent* clone(void) const {
        return nullptr;
    }
};


class CExplosionCreator :
    public BaseCreator<IComponent> {

public:
    IComponent* create(rapidxml::xml_node<> *node) {
        return new CExplosion();
    }
};
#endif