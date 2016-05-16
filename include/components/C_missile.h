#ifndef C_INFORMATION_H_
#define C_INFORMATION_H_

#include "entity/entity.h"
#include "entity/component.h"
#include "entity/actorFactory.h"
#include "scripting/laccessor.h"

using Compote::Entity::AbstractComponentFactory;
using Compote::Script::LuaAccessor;
using namespace Compote::Component;
using Compote::Entity::entityID;

class CMissile : public IComponent {
public:
    entityID m_throwerID;
    bool m_bThrowerStillImmune;

    const static ComponentType sk_componentType;

    CMissile() :
        m_throwerID(-1),
        m_bThrowerStillImmune(true) {}

    virtual ~CMissile() {}

    inline const ComponentType getComponentType(void) const override {
        return CMissile::sk_componentType;
    }

    static const char* getName(void) {
        return "CMissile";
    }

    IComponent* clone(void) const override {
        return nullptr;
    }

};


class CMissileFactory : public AbstractComponentFactory<CMissile> {
public:
    CMissileFactory() {}
    ~CMissileFactory() {}

    IComponent* createWithLuaDatas(LuaAccessor& accessor) const {
        return new CMissile();
    }
};
#endif