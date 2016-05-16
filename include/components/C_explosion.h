#ifndef _C_EXPLOSION_H_
#define _C_EXPLOSION_H_

#include "entity/component.h"
#include "entity/actorFactory.h"
#include "scripting/laccessor.h"

using Compote::Entity::AbstractComponentFactory;
using Compote::Script::LuaAccessor;

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

    inline const ComponentType getComponentType(void) const override {
        return CExplosion::sk_componentType;
    }

    static const char* getName(void) {
        return "CExplosion";
    }

    IComponent* clone(void) const override {
        return nullptr;
    }
};


class CExplosionFactory : public AbstractComponentFactory<CExplosion> {
public:
    CExplosionFactory() {}
    ~CExplosionFactory() {}

    IComponent* createWithLuaDatas(LuaAccessor& accessor) const {
        return new CExplosion();
    }
};


#endif