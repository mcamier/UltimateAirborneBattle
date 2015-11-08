#ifndef C_INFORMATION_H_
#define C_INFORMATION_H_

#include "CPT_entity.h"
#include "CPT_component.h"
#include "CPT_creator.h"
#include "rapidxml\rapidxml.hpp"

class CMissile : public IComponent {
public:
    entityID m_throwerID;
    bool m_bThrowerStillImmune;

    const static ComponentType sk_componentType;

    CMissile() :
        m_throwerID(-1),
        m_bThrowerStillImmune(true) {}

    virtual ~CMissile() {}

    inline const ComponentType getComponentType(void) const {
        return CMissile::sk_componentType;
    }

    static const char* getName(void) {
        return "CMissile";
    }

    IComponent* clone(void) const {
        return nullptr;
    }


};


class CMissileCreator :
    public BaseCreator<IComponent> {

public:
    IComponent* create(rapidxml::xml_node<> *node) {
        return new CMissile();
    }
};
#endif