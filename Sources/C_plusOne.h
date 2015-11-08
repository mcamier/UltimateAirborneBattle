#ifndef _C_PLUS_ONE_H_
#define _C_PLUS_ONE_H_

#include "CPT_component.h"
#include "CPT_creator.h"
#include "rapidxml\rapidxml.hpp"

class CPlusOne : public IComponent {
public:
    const static ComponentType sk_componentType;

public:
    float m_elapsedTime = 0;
    float m_lifeTimeDuration = 2000;


    CPlusOne() {}

    virtual ~CPlusOne() {}

    inline const ComponentType getComponentType(void) const {
        return CPlusOne::sk_componentType;
    }

    static const char* getName(void) {
        return "CPlusOne";
    }

    IComponent* clone(void) const {
        return nullptr;
    }
};


class CPlusOneCreator :
    public BaseCreator<IComponent> {

public:
    IComponent* create(rapidxml::xml_node<> *node) {
        return new CPlusOne();
    }
};

#endif