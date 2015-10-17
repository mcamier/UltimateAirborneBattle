#ifndef _C_PLUS_ONE_H_
#define _C_PLUS_ONE_H_

#include "CPT_component.h"

class CPlusOne : public IComponent {
public:
    const static ComponentType sk_componentType = 0x5128c722;

public:
    float m_elapsedTime = 0;
    float m_lifeTimeDuration = 2000;


    CPlusOne() {}

    virtual ~CPlusOne() {}

    inline const ComponentType getComponentType(void) const {
        return CPlusOne::sk_componentType;
    }

    inline const char* getName(void) const {
        return "CPlusOne";
    }
};

#endif