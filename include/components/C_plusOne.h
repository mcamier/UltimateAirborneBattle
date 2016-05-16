#ifndef _C_PLUS_ONE_H_
#define _C_PLUS_ONE_H_

#include "entity/component.h"
#include "entity/actorFactory.h"
#include "scripting/laccessor.h"

using Compote::Entity::AbstractComponentFactory;
using Compote::Script::LuaAccessor;
using namespace Compote::Component;

class CPlusOne : public IComponent {
public:
    const static ComponentType sk_componentType;

public:
    float m_elapsedTime = 0;
    float m_lifeTimeDuration = 2000;


    CPlusOne() {}

    virtual ~CPlusOne() {}

    inline const ComponentType getComponentType(void) const override {
        return CPlusOne::sk_componentType;
    }

    static const char* getName(void) {
        return "CPlusOne";
    }

    IComponent* clone(void) const override{
        return nullptr;
    }
};


class CPlusOneFactory : public AbstractComponentFactory<CPlusOne> {
public:
    CPlusOneFactory() {}
    ~CPlusOneFactory() {}

    IComponent* createWithLuaDatas(LuaAccessor& accessor) const {
        return new CPlusOne();
    }
};

#endif