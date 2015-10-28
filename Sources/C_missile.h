#ifndef C_INFORMATION_H_
#define C_INFORMATION_H_

#include "CPT_entity.h"
#include "CPT_component.h"

class CMissile : public IComponent {
public:
    entityID m_throwerID;
    bool m_bThrowerStillImmune;

    const static ComponentType sk_componentType;

    CMissile(entityID throwerID) :
        m_throwerID(throwerID),
        m_bThrowerStillImmune(true) {}

    virtual ~CMissile() {}

    inline const ComponentType getComponentType(void) const {
        return CMissile::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CMissile";
    }
};

#endif